#pragma once

#include <vector>
#include <thread>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

namespace http {
namespace server {

class IoContextPool : public boost::noncopyable
{
public:
    IoContextPool();

    void run();

    void stop();

    boost::asio::io_context& io_context();

private:
    struct Context {
        boost::asio::io_context io_context;
        std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> guard;
        std::thread thread;
    };
    std::vector<Context> contexts_;
    size_t next_context;
};

}
}
