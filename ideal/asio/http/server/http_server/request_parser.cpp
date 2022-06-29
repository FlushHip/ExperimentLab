#include "request_parser.hpp"

namespace http {
namespace server {

RequestParser::RequestParser()
    : state_(method_start)
{

}

void RequestParser::reset()
{
    state_ = method_start;
}

boost::tribool RequestParser::consume(Request &request, char c)
{
    switch (state_)
    {
    case method_start:
        if (!is_char(c) || is_ctl(c) || is_tspecial(c)) {
            return false;
        } else {
            state_ = method;
            request.method.push_back(c);
            return boost::indeterminate;
        }
    case method:
        if (c == ' ') {
            state_ = uri;
            return boost::indeterminate;
        } else if (!is_char(c) || is_ctl(c) || is_tspecial(c)) {
            return false;
        } else {
            request.method.push_back(c);
            return boost::indeterminate;
        }
    case uri:
        if (c == ' ') {
            state_ = http_version_h;
            return boost::indeterminate;
        } else if (is_ctl(c)) {
            return false;
        } else {
            request.uri.push_back(c);
            return boost::indeterminate;
        }
    case http_version_h:
        if (c == 'H') {
            state_ = http_version_t_1;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_t_1:
        if (c == 'T') {
            state_ = http_version_t_2;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_t_2:
        if (c == 'T') {
            state_ = http_version_p;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_p:
        if (c == 'P') {
            state_ = http_version_slash;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_slash:
        if (c == '/') {
            request.http_version_major = 0;
            request.http_version_minor = 0;
            state_ = http_version_major_start;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_major_start:
        if (is_digit(c)) {
            request.http_version_major = request.http_version_major * 10 + c - '0';
            state_ = http_version_major;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_major:
        if (c == '.') {
            state_ = http_version_minor_start;
            return boost::indeterminate;
        } else if (is_digit(c)) {
            request.http_version_major = request.http_version_major * 10 + c - '0';
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_minor_start:
        if (is_digit(c)) {
            request.http_version_minor = request.http_version_minor * 10 + c - '0';
            state_ = http_version_minor;
            return boost::indeterminate;
        } else {
            return false;
        }
    case http_version_minor:
        if (c == '\r') {
            state_ = expecting_newline_1;
            return boost::indeterminate;
        } else if (is_digit(c)) {
            request.http_version_minor = request.http_version_minor * 10 + c - '0';
            return boost::indeterminate;
        } else {
            return false;
        }
    case expecting_newline_1:
        if (c == '\n') {
            state_ = header_line_start;
            return boost::indeterminate;
        } else {
            return false;
        }
    case header_line_start:
        if (c == '\r') {
            state_ = expecting_newline_3;
            return boost::indeterminate;
        } else if (!request.headers.empty() && (c == ' ' || c == '\t')) {
            state_ = header_lws;
            return boost::indeterminate;
        } else if (!is_char(c) || is_ctl(c) || is_tspecial(c)) {
            return false;
        } else {
            request.headers.push_back(Header());
            request.headers.back().name.push_back(c);
            state_ = header_name;
            return boost::indeterminate;
        }
    case header_lws:
        if (c == '\r') {
            state_ = expecting_newline_2;
            return boost::indeterminate;
        } else if (c == ' ' || c == '\t') {
            return boost::indeterminate;
        } else if (is_ctl(c)) {
            return false;
        } else {
            state_ = header_value;
            request.headers.back().value.push_back(c);
            return boost::indeterminate;
        }
    case header_name:
        if (c == ':') {
            state_ = space_before_header_value;
            return boost::indeterminate;
        } else if (!is_char(c) || is_ctl(c) || is_tspecial(c)) {
            return false;
        } else {
            request.headers.back().name.push_back(c);
            return boost::indeterminate;
        }
    case space_before_header_value:
        if (c == ' ') {
            state_ = header_value;
            return boost::indeterminate;
        } else {
            return false;
        }
    case header_value:
        if (c == '\r') {
            state_ = expecting_newline_2;
            return boost::indeterminate;
        } else if (is_ctl(c)) {
            return false;
        } else {
            request.headers.back().value.push_back(c);
            return boost::indeterminate;
        }
    case expecting_newline_2:
        if (c == '\n') {
            state_ = header_line_start;
            return boost::indeterminate;
        } else {
            return false;
        }
    case expecting_newline_3:
        return (c == '\n');
    default:
        return false;
    }
}

bool RequestParser::is_char(int c)
{
    return c >= 0 && c <= 127;
}

bool RequestParser::is_ctl(int c)
{
    return (c >= 0 && c <= 31) || (c == 127);
}

bool RequestParser::is_tspecial(int c)
{
    switch (c)
    {
    case '(':
    case ')':
    case '<':
    case '>':
    case '@':
    case ',':
    case ';':
    case ':':
    case '\\':
    case '"':
    case '/':
    case '[':
    case ']':
    case '?':
    case '=':
    case '{':
    case '}':
    case ' ':
    case '\t':
        return true;
    default:
        return false;
    }
}

bool RequestParser::is_digit(int c)
{
    return c >= '0' && c <= '9';
}

}
}
