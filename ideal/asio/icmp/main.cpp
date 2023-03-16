#include <boost/asio/error.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/process/environment.hpp>
#include <boost/system/error_code.hpp>

#include <chrono>
#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string_view>

#include <spdlog/spdlog.h>

namespace icmp {

namespace header {

class icmp_header {
public:
    enum {
        echo_reply = 0,
        destination_unreachable = 3,
        source_quench = 4,
        redirect = 5,
        echo_request = 8,
        time_exceeded = 11,
        parameter_problem = 12,
        timestamp_request = 13,
        timestamp_reply = 14,
        info_request = 15,
        info_reply = 16,
        address_request = 17,
        address_reply = 18,
    };

    std::uint8_t type() const { return req_[0]; };
    std::uint8_t code() const { return req_[1]; };
    std::uint16_t checksum() const { return decode(2); };
    std::uint16_t identifier() const { return decode(4); };
    std::uint16_t sequence_number() const { return decode(6); };

    void type(std::uint8_t b) { req_[0] = b; };
    void code(std::uint8_t b) { req_[1] = b; };
    void checksum(std::uint16_t u) { encode(u, 2); };
    void identifier(std::uint16_t u) { encode(u, 4); };
    void sequence_number(std::uint16_t u) { encode(u, 6); };

    friend std::ostream& operator<<(std::ostream& os,
        const icmp_header& header) {
        return os.write(
            reinterpret_cast<const char*>(header.req_), sizeof(header.req_));
    }

    friend std::istream& operator>>(std::istream& is, icmp_header& header) {
        return is.read(
            reinterpret_cast<char*>(header.req_), sizeof(header.req_));
    }

private:
    std::uint16_t decode(int begin) const {
        return (req_[begin] << 8) + req_[begin + 1];
    }

    void encode(std::uint16_t u, int begin) {
        req_[begin] = u >> 8;
        req_[begin + 1] = u & 0xFF;
    }

private:
    std::uint8_t req_[8] = {0};
};

template <typename Iterator>
void compute_checksum(icmp_header& header,
    Iterator body_begin,
    Iterator body_end) {
    unsigned int sum = (header.type() << 8) + header.code() +
        header.identifier() + header.sequence_number();

    Iterator body_iter = body_begin;
    while (body_iter != body_end) {
        sum += (static_cast<unsigned char>(*body_iter++) << 8);
        if (body_iter != body_end)
            sum += static_cast<unsigned char>(*body_iter++);
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    header.checksum(static_cast<unsigned short>(~sum));
}

class ipv4_header {
public:
    ipv4_header() { std::fill(rep_, rep_ + sizeof(rep_), 0); }

    unsigned char version() const { return (rep_[0] >> 4) & 0xF; }
    unsigned short header_length() const { return (rep_[0] & 0xF) * 4; }
    unsigned char type_of_service() const { return rep_[1]; }
    unsigned short total_length() const { return decode(2, 3); }
    unsigned short identification() const { return decode(4, 5); }
    bool dont_fragment() const { return (rep_[6] & 0x40) != 0; }
    bool more_fragments() const { return (rep_[6] & 0x20) != 0; }
    unsigned short fragment_offset() const { return decode(6, 7) & 0x1FFF; }
    unsigned int time_to_live() const { return rep_[8]; }
    unsigned char protocol() const { return rep_[9]; }
    unsigned short header_checksum() const { return decode(10, 11); }

    boost::asio::ip::address_v4 source_address() const {
        boost::asio::ip::address_v4::bytes_type bytes = {
            {rep_[12], rep_[13], rep_[14], rep_[15]}};
        return boost::asio::ip::address_v4(bytes);
    }

    boost::asio::ip::address_v4 destination_address() const {
        boost::asio::ip::address_v4::bytes_type bytes = {
            {rep_[16], rep_[17], rep_[18], rep_[19]}};
        return boost::asio::ip::address_v4(bytes);
    }

    friend std::istream& operator>>(std::istream& is, ipv4_header& header) {
        is.read(reinterpret_cast<char*>(header.rep_), 20);
        if (header.version() != 4)
            is.setstate(std::ios::failbit);
        std::streamsize options_length = header.header_length() - 20;
        if (options_length < 0 || options_length > 40)
            is.setstate(std::ios::failbit);
        else
            is.read(reinterpret_cast<char*>(header.rep_) + 20, options_length);
        return is;
    }

private:
    unsigned short decode(int a, int b) const {
        return (rep_[a] << 8) + rep_[b];
    }

    unsigned char rep_[60];
};

}  // namespace header

class pinger {
public:
    pinger(const pinger& other) = delete;
    pinger& operator=(const pinger& other) = delete;

public:
    explicit pinger(std::string_view host)
        : io_context_(1)
        , socket_(io_context_, boost::asio::ip::icmp::v4())
        , timer_(io_context_) {
        boost::asio::ip::icmp::resolver resolver(io_context_);
        endpoint_ = *resolver.resolve(host, "").begin();

        SPDLOG_INFO(
            "icmp resolve result ip : {}", endpoint_.address().to_string());

        do_send();
        do_receive();
    }

    void run() { io_context_.run(); }

private:
    void do_send() {
        header::icmp_header icmp_header;
        std::string body("flushhip");
        icmp_header.type(header::icmp_header::echo_request);
        icmp_header.code(0);
        icmp_header.identifier((std::uint16_t)boost::this_process::get_id());
        icmp_header.sequence_number((std::uint16_t)++sequence_num_);
        header::compute_checksum(icmp_header, body.begin(), body.end());

        boost::asio::streambuf buffer;
        std::ostream os(&buffer);
        os << icmp_header << body;

        time_sent_ = std::chrono::steady_clock::now();
        num_replies_ = 0;
        socket_.send_to(buffer.data(), endpoint_);

        using namespace std::literals::chrono_literals;
        timer_.expires_at(time_sent_ + 5s);
        timer_.async_wait([this](const boost::system::error_code& ec) {
            if (ec != boost::asio::error::operation_aborted) {
                SPDLOG_CRITICAL("Request timeout");
            }

            timer_.expires_at(time_sent_ + 1s);
            timer_.async_wait(std::bind(&pinger::do_send, this));
        });
    }

    void do_receive() {
        reply_buffer_.consume(reply_buffer_.size());
        socket_.async_receive(reply_buffer_.prepare(64 * 1024),
            [this](const boost::system::error_code& ec, std::size_t length) {
                if (!ec) {
                    reply_buffer_.commit(length);
                    std::istream is(&reply_buffer_);
                    header::ipv4_header ipv4_header;
                    header::icmp_header icmp_header;
                    is >> ipv4_header >> icmp_header;

                    if (is &&
                        icmp_header.type() == header::icmp_header::echo_reply &&
                        icmp_header.sequence_number() == sequence_num_ &&
                        icmp_header.identifier() ==
                            boost::this_process::get_id()) {
                        if (num_replies_++ == 0) {
                            timer_.cancel();
                        }

                        auto elapsed =
                            std::chrono::steady_clock::now() - time_sent_;
                        std::stringstream strs;
                        strs << length - ipv4_header.header_length()
                             << " bytes from " << ipv4_header.source_address()
                             << ": icmp_seq=" << icmp_header.sequence_number()
                             << ", ttl=" << ipv4_header.time_to_live()
                             << ", time="
                             << std::chrono::duration_cast<
                                    std::chrono::milliseconds>(elapsed)
                                    .count();
                        SPDLOG_INFO(strs.str());
                    }

                    do_receive();
                }
            });
    }

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::icmp::socket socket_;
    boost::asio::ip::icmp::endpoint endpoint_;
    boost::asio::streambuf reply_buffer_;

    boost::asio::steady_timer timer_;
    std::chrono::steady_clock::time_point time_sent_;
    std::size_t sequence_num_ = 0;
    std::size_t num_replies_ = 0;
};

}  // namespace icmp

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    using namespace std::literals::string_view_literals;
    constexpr auto host = "www.baidu.com"sv;

    try {
        icmp::pinger pinger(host);
        pinger.run();
    } catch (const std::exception& e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
