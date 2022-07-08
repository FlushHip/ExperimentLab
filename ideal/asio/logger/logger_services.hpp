#pragma once

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/system/error_code.hpp>

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

namespace services {

class logger_service : public boost::asio::execution_context::service {
public:
    using key_type = logger_service;

    struct logger_impl {
        explicit logger_impl(const std::string& identifier)
            : identifier(identifier) {}
        std::string identifier;
    };
    using impl_type = logger_impl*;

    logger_service(boost::asio::execution_context& context)
        : boost::asio::execution_context::service(context)
        , io_context_(1)
        , work_(boost::asio::require(io_context_.get_executor(),
              boost::asio::execution::outstanding_work.tracked))
        , thread_([this] { io_context_.run(); }) {}

    ~logger_service() {
        work_ = boost::asio::any_io_executor();
        if (thread_.joinable())
            thread_.join();
    }

    impl_type null() const { return nullptr; }

    void create(impl_type& impl, const std::string& identifier) {
        impl = new logger_impl(identifier);
    }

    void destroy(impl_type& impl) {
        delete impl;
        impl = nullptr;
    }

    void shutdown() {}

    void use_file(impl_type&, const std::string& file) {
        boost::asio::post(
            io_context_, std::bind(&logger_service::use_file_impl, this, file));
    }

    void log(impl_type& impl, const std::string& message) {
        std::ostringstream os;
        os << impl->identifier << ": " << message;

        boost::asio::post(
            io_context_, std::bind(&logger_service::log_impl, this, os.str()));
    }

private:
    void use_file_impl(const std::string& file) {
        ofstream_.close();
        ofstream_.clear();
        ofstream_.open(file);
        if (!ofstream_.is_open()) {
            std::cerr << "ofstream is not open : " << file << std::endl;
        }
    }

    void log_impl(const std::string& message) {
        std::cout << message << std::endl;
        ofstream_ << message << std::endl;
    }

private:
    boost::asio::io_context io_context_;
    boost::asio::any_io_executor work_;

    std::thread thread_;
    std::ofstream ofstream_;
};

}  // namespace services
