#include <iostream>
#include <string_view>

#include <boost/asio.hpp>

#include <spdlog/spdlog.h>

namespace icmp {

namespace header {

class icmp_header
{
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

    std::byte type() const { return req_[0]; };
    std::byte code() const { return req_[1]; };
    std::uint16_t checksum() const { return decode(2); };
    std::uint16_t identifier() const { return decode(4); };
    std::uint16_t sequence_number() const { return decode(6); };

    void type(std::byte b) { req_[0] = b; };
    void code(std::byte b) { req_[1] = b; };
    void checksum(std::uint16_t u) { encode(u, 2); };
    void identifier(std::uint16_t u) { encode(u, 4); };
    void sequence_number(std::uint16_t u) { encode(u, 6); };

private:
    std::uint16_t decode(int begin) const
    {
        return (std::uint16_t)(req_[begin] << 8) + (std::uint16_t)req_[begin + 1];
    }

    void encode(std::uint16_t u, int begin)
    {
        req_[begin] = (std::byte)(u >> 8);
        req_[begin + 1] = (std::byte)(u & 0xFF);
    }

private:
    std::byte req_[8];
};

}

class pinger
{
public:
    pinger(const pinger &other) = delete;
    pinger& operator=(const pinger &other) = delete;

public:
    explicit pinger(std::string_view host)
        : io_context_(1)
        , socket_(io_context_)
        , timer_(io_context_)
    {
        boost::asio::ip::icmp::resolver resolver(io_context_);
        endpoint_ = *resolver.resolve(host, "").begin();

        SPDLOG_INFO("icmp resolve result ip : {}", endpoint_.address().to_string());

        do_send();
        do_receive();
    }

    void run()
    {
        io_context_.run();
    }

private:
    void do_send()
    {

    }


    void do_receive()
    {

    }

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::icmp::socket socket_;
    boost::asio::ip::icmp::endpoint endpoint_;

    boost::asio::steady_timer timer_;
    std::size_t sequence_num_;
    std::size_t num_replies_;
};

}

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    using namespace std::literals::string_view_literals;
    constexpr auto host = "www.baidu.com"sv;

    try {
        icmp::pinger pinger(host);
        pinger.run();
    } catch (const std::exception &e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
