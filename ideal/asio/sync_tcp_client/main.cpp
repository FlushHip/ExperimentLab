#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

std::string random_string()
{
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
            size_t len = str.size();
            std::copy(reinterpret_cast<const char *>(&len), reinterpret_cast<const char *>(&len + 1), buff.data());
            std::copy(str.begin(), str.end(), buff.data() + 4);

            boost::asio::write(socket, boost::asio::buffer(buff));
            SPDLOG_INFO("send msg : [{}]", str);

            boost::asio::read(socket, boost::asio::buffer(buff), boost::asio::transfer_exactly(4));
            uint32_t recv_len = *(reinterpret_cast<const uint32_t *>(buff.data()));
            SPDLOG_TRACE("recv msg len is <{}>", recv_len);
            boost::asio::read(socket, boost::asio::buffer(buff), boost::asio::transfer_exactly(recv_len));
            SPDLOG_INFO("recv msg : [{}]", std::string(buff.data(), recv_len));

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (std::exception &e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
