#pragma once

#include <boost/asio/execution_context.hpp>
namespace services {

template <typename Services>
class basic_logger {
public:
    basic_logger(const basic_logger<Services>&) = delete;
    basic_logger<Services>& operator=(const basic_logger<Services>&) = delete;

    using service_type = Services;
    using impl_type = typename service_type::impl_type;

    explicit basic_logger(boost::asio::execution_context& context,
        const std::string& identifier)
        : service_(boost::asio::use_service<Services>(context))
        , impl_(service_.null()) {
        service_.create(impl_, identifier);
    }

    ~basic_logger() { service_.destroy(impl_); }

    void use_file(const std::string& file) { service_.use_file(impl_, file); };

    void log(const std::string& message) { service_.log(impl_, message); }

private:
    service_type& service_;
    impl_type impl_;
};

}  // namespace services
