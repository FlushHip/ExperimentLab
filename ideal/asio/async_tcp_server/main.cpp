#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>


class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(boost::asio::io_context &io)
        : socket_(io)
        , pool_(1)
    {
    }

    boost::asio::ip::tcp::socket& socket() { return socket_; };

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        boost::asio::async_read(socket_, boost::asio::buffer(buffer_), boost::asio::transfer_exactly(4)
            , [this, self = shared_from_this()](const boost::system::error_code &ec, size_t size)
        {
            if (ec) {
                SPDLOG_ERROR(ec.message());
                return ;
            }
            uint32_t data_length = *reinterpret_cast<const uint32_t *>(buffer_.data());
            boost::asio::async_read(socket_, boost::asio::buffer(buffer_), boost::asio::transfer_exactly(data_length - size + 4)
                , [this, self = shared_from_this()](const boost::system::error_code &ec, size_t size)
            {
                if (ec) {
                    SPDLOG_ERROR(ec.message());
                    return ;
                }
                SPDLOG_INFO("recv msg [{}]", std::string(buffer_.data(), size));
                boost::asio::post(pool_, std::bind([this, self = shared_from_this(), size]
                {
                    uint32_t len = size;
                    std::copy(buffer_.data(), buffer_.data() + size, buffer_.data() + 4);
                    std::copy(reinterpret_cast<const char *>(&len), reinterpret_cast<const char *>(&len + 1), buffer_.data());
                    boost::asio::write(socket_, boost::asio::buffer(buffer_.data(), size));

                    SPDLOG_INFO("write msg [{}]", std::string(buffer_.data(), size + 4));
                }));

                do_read();
            });
        });
    }

    boost::asio::thread_pool pool_;
    boost::asio::ip::tcp::socket socket_;
    std::array<char, 2048> buffer_;
};

class TcpServer
{
public:
    TcpServer(boost::asio::io_context &io) : io_(io)
        , acceptor_(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345))
    {
        auto local_endpoint = acceptor_.local_endpoint();
        SPDLOG_INFO("server protocol : {}, ip : {}, port : {}."
            , local_endpoint.protocol().family(), local_endpoint.address().to_string(), local_endpoint.port());
        do_accept();
    }

    auto start() { io_.run(); };

private:
    void do_accept()
    {
        auto connection = std::make_shared<TcpConnection>(io_);
        acceptor_.async_accept(connection->socket(), std::bind([connection, this](const boost::system::error_code &ec)
        {
            if (!ec) {
                connection->start();
                SPDLOG_TRACE("new connection");
            } else {
                SPDLOG_ERROR(ec.message());
            }

            do_accept();
        }, std::placeholders::_1));
    }

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_context &io_;
};

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    try {
        boost::asio::io_context io;
        TcpServer server(io);
        server.start();
    } catch (std::exception &e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
