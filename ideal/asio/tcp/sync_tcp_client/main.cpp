#include <iostream>
#include <charconv>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

std::string random_string()
{
    srand(time(nullptr));

    auto length = rand() % 48 + 1;
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    try {
        boost::asio::io_context io;

        boost::asio::ip::tcp::socket socket(io);

        std::vector<boost::asio::ip::tcp::endpoint> endpoints{ boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 12345) };
        auto result = boost::asio::connect(socket, endpoints);
        SPDLOG_INFO("client connect ip {}, port {}", result.address().to_string(), result.port());

        for (std::array<char, 2048> buff; ;) {
            boost::system::error_code ec;

            auto str = random_string();

            // len + body
            uint32_t len = str.size();
            //   len
            std::fill_n(buff.data(), 4, 0);
            std::to_chars(buff.data(), buff.data() + 4, len);
            boost::asio::write(socket, boost::asio::buffer(buff), boost::asio::transfer_exactly(4));
            //   body
            boost::asio::write(socket, boost::asio::buffer(str), boost::asio::transfer_exactly(len));
            SPDLOG_INFO("send msg : [{}]", str);

            //   len
            boost::asio::read(socket, boost::asio::buffer(buff), boost::asio::transfer_exactly(4));
            uint32_t recv_len = 0;
            std::from_chars(buff.data(), buff.data() + 4, recv_len);
            SPDLOG_TRACE("recv msg len is <{}>", recv_len);
            //   body
            boost::asio::read(socket, boost::asio::buffer(buff), boost::asio::transfer_exactly(recv_len));
            SPDLOG_INFO("recv msg : [{}]", std::string(buff.data(), recv_len));

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (std::exception &e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
