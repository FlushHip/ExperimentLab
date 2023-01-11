#pragma once

#include <functional>
#include <memory>
#include <string_view>
#include <unordered_map>

namespace hestina {

class tcp_server;
class http_request;
class http_response;
class connection;
class buffer;

class http_server {
public:
    http_server(std::string_view ip, uint16_t port);
    ~http_server();

    bool start();
    bool stop();

    using handler_t = std::function<void(const hestina::http_request& request,
        hestina::http_response& response)>;
    void register_handler(std::string_view path, handler_t&& handler);

private:
    void do_new_connection(const std::weak_ptr<connection>& conn);
    void do_read(const std::weak_ptr<connection>& conn, buffer* buff);

    void on_request(const http_request& request, http_response& response);

    std::unique_ptr<tcp_server> server_;
    std::unordered_map<std::string_view, handler_t> handlers_;
};

}  // namespace hestina
