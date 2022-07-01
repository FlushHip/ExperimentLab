#pragma once

#include <boost/logic/tribool.hpp>

#include "request.hpp"

namespace http {
namespace server {

class RequestParser
{
public:
    RequestParser();

    void reset();

    std::string_view raw_string() { return raw_string_; };

    template<typename InputIterator>
    std::tuple<boost::tribool, InputIterator>
        parse(Request &request, InputIterator begin, InputIterator end)
    {
        while (begin != end) {
            raw_string_.push_back(static_cast<char>(*begin));
            auto result = consume(request, *begin++);
            if (result || !result) {
                return { result, begin };
            }
        }
        return {boost::indeterminate, begin};
    }

private:
    boost::tribool consume(Request &request, char c);

    static bool is_char(int c);
    static bool is_ctl(int c);
    static bool is_tspecial(int c);
    static bool is_digit(int c);

    enum state
    {
        method_start,
        method,
        uri,
        http_version_h,
        http_version_t_1,
        http_version_t_2,
        http_version_p,
        http_version_slash,
        http_version_major_start,
        http_version_major,
        http_version_minor_start,
        http_version_minor,
        expecting_newline_1,
        header_line_start,
        header_lws,
        header_name,
        space_before_header_value,
        header_value,
        expecting_newline_2,
        expecting_newline_3
    } state_;

    std::string raw_string_;
};

}
}
