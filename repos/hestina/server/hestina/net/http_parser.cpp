#include "http_parser.h"

#include <hestina/log/logger.h>
#include <hestina/net/buffer.h>

#include <cassert>
#include <cctype>

namespace hestina {

http_parser::http_parser() = default;

http_parser::~http_parser() = default;

bool http_parser::parse_request(buffer* buff) {
    using namespace std::string_view_literals;
    auto crlf = "\r\n"sv;
    auto space = " "sv;
    while (true) {
        switch (status_) {
        case parse_status::kmethod: {
            auto num = buff->find(space);
            if (num == buffer::sinvalid) {
                return false;
            }
            request_.method_ = to_method(buff->read(num));
            buff->retrieve(space.size());
            status_ = parse_status::kpath;
            break;
        }
        case parse_status::kpath: {
            auto num = buff->find(space);
            if (num == buffer::sinvalid) {
                return false;
            }
            request_.path_ = buff->read(num);
            buff->retrieve(space.size());
            status_ = parse_status::kversion;
            break;
        }
        case parse_status::kversion: {
            auto num = buff->find(crlf);
            if (num == buffer::sinvalid) {
                return false;
            }
            request_.version_ = to_version(buff->read(num));
            buff->retrieve(crlf.size());
            status_ = parse_status::kheaders;
            break;
        }
        case parse_status::kheaders: {
            auto num = buff->find(crlf);
            if (num == buffer::sinvalid) {
                return false;
            }
            if (num == 0) {
                buff->retrieve(crlf.size());
                status_ = parse_status::kbody;
                break;
            }
            auto line = buff->read(num);
            buff->retrieve(crlf.size());

            auto pos = line.find(':');
            std::string lhs(line.substr(0, pos));
            for (++pos; pos < line.size() && std::isspace(line[pos]); ++pos) {
            }
            std::string rhs(line.substr(pos));
            request_.headers_.emplace(std::move(lhs), std::move(rhs));
            break;
        }
        case parse_status::kbody:
            // TODO (flushhip): deal body
            status_ = parse_status::kmethod;
            return true;
            break;
        case parse_status::kend:
            status_ = parse_status::kmethod;
            return true;
        default:
            assert(false);
        }
    }
    return false;
}

const http_request& http_parser::request() const {
    return request_;
}

}  // namespace hestina
