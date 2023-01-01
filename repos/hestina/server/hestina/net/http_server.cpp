#include "http_server.h"

#include <hestina/log/logger.h>
#include <hestina/net/connection.h>
#include <hestina/net/http_parser.h>
#include <hestina/net/http_request.h>
#include <hestina/net/http_response.h>
#include <hestina/net/tcp_server.h>

#include <memory>

namespace hestina {
http_server::http_server(std::string_view ip, uint16_t port)
    : server_(std::make_unique<tcp_server>(port, ip)) {
    server_->set_new_connection_callback([this](auto&& PH) {
        do_new_connection(std::forward<decltype(PH)>(PH));
    });
    server_->set_data_arrive_callback([this](auto&& PH1, auto&& PH2) {
        do_read(
            std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
}

http_server::~http_server() = default;

bool http_server::start() {
    return server_->start();
}

bool http_server::stop() {
    return server_->stop();
}

void http_server::register_handler(std::string_view path, handler_t&& handler) {
    if (handlers_.contains(path)) {
        log_warn << path << " handler will be override.";
    }
    handlers_[path] = handler;
}

void http_server::do_new_connection(const std::weak_ptr<connection>& conn) {
    if (auto con = conn.lock()) {
        con->set_context(std::make_shared<http_parser>());
    }
}

void http_server::do_read(const std::weak_ptr<connection>& conn, buffer* buff) {
    if (auto con = conn.lock()) {
        auto parser = con->get_context<http_parser>();
        if (parser->parse_request(buff)) {
            http_request request = parser->request();
            http_response response(request.version());
            on_request(request, response);

            if (auto con = conn.lock()) {
                bool should_close =
                    (request.version() == version_t::khttp10 &&
                        (!request.headers().contains(kconnection.data()) ||
                            request.headers().at(kconnection.data()) ==
                                kconnection_close)) ||
                    (request.version() == version_t::khttp11 &&
                        request.headers().contains(kconnection.data()) &&
                        request.headers().at(kconnection.data()) ==
                            kconnection_close);
                response.add_header(kconnection.data(),
                    should_close ? kconnection_close.data()
                                 : kconnection_keep_alive.data());

                // response to client
                con->send(response.data());

                if (should_close) {
                    con->close();
                }
            }
        }
    }
}

void http_server::on_request(const http_request& request,
    http_response& response) {
    if (!handlers_.contains(request.path())) {
        response.set_code(status_code_t::knot_find);
    } else {
        handlers_[request.path()](request, response);
    }
}

}  // namespace hestina
