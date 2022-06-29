#include "request_handler.hpp"

#include <sstream>
#include <fstream>
#include <filesystem>

#include "request.hpp"
#include "reply.hpp"
#include "mime_types.hpp"

namespace http {
namespace server {

RequestHandler::RequestHandler(std::string_view doc_root)
    : doc_root_(doc_root)
{

}

void RequestHandler::handle_request(const Request & request, Reply &reply)
{
    std::string request_path;
    if (!url_decode(request.uri, request_path)) {
        reply = Reply::stock_reply(Reply::status_type::bad_request);
        return;
    }

    if (request_path.empty() || request_path[0] != '/' || request_path.find("..") != std::string::npos) {
        reply = Reply::stock_reply(Reply::status_type::bad_request);
        return;
    }

    if (request_path.back() == '/') {
        request_path += "index.html";
    }

    auto last_slash_pos = request_path.find_last_of("/");
    auto last_dot_pos = request_path.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
        extension = request_path.substr(last_dot_pos + 1);
    }

    auto full_path = std::filesystem::path(doc_root_) / request_path;
    std::ifstream is(full_path, std::ios::in | std::ios::binary);
    if (!is) {
        reply = Reply::stock_reply(Reply::not_found);
        return ;
    }

    for (std::array<char, 1024> buff; is.read(buff.data(), buff.max_size()).gcount() > 0; ) {
        reply.content.append(buff.data(), is.gcount());
    }

    reply.status = Reply::status_type::ok;
    reply.headers.reserve(2);
    reply.headers[0].name = "Content-Length";
    reply.headers[0].value = std::to_string(reply.content.size());
    reply.headers[1].name = "Content-Type";
    reply.headers[1].value = mime_types::extension_to_type(extension);
}

bool RequestHandler::url_decode(const std::string &in, std::string &out)
{
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%') {
            if (i + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    i += 2;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (in[i] == '+') {
            out += ' ';
        } else {
            out += in[i];
        }
    }
    return true;
}

}
}
