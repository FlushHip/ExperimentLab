#pragma once

#include <string>

#include <boost/noncopyable.hpp>

namespace http {
namespace server {

struct Request;
struct Reply;

class RequestHandler : public boost::noncopyable
{
public:
    explicit RequestHandler(std::string_view doc_root);

    void handle_request(const Request & request, Reply &reply);
private:
    static bool url_decode(const std::string &in, std::string &out);

    std::string doc_root_;
};

}
}
