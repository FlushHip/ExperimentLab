#include "http_response.h"

#include <hestina/log/logger.h>
#include <hestina/net/http_common.h>
#include <string>
#include <unordered_map>

namespace hestina {

http_response::http_response(version_t version, status_code_t code)
    : version_(version), code_(code) {}

status_code_t http_response::code() const {
    return code_;
}

void http_response::set_code(status_code_t code) {
    code_ = code;
}

const std::unordered_map<std::string, std::string>& http_response::headers()
    const {
    return headers_;
}

void http_response::add_header(const std::string& lhs, const std::string& rhs) {
    if (headers_.contains(lhs)) {
        log_warn << "header " << lhs << ": " << headers_[lhs]
                 << " will be override by " << rhs << ".";
        headers_[lhs] = rhs;
    } else {
        headers_.emplace(lhs, rhs);
    }
}

std::string_view http_response::body() const {
    return body_;
}

void http_response::set_body(std::string_view body) {
    body_ = body;
}

content_type_t http_response::content_type() const {
    return type_;
}

void http_response::set_content_type(content_type_t type) {
    type_ = type;
}

std::string http_response::data() const {
    std::string ret;

    using namespace std::string_literals;
    auto space = " "s;
    auto crlf = "\r\n"s;

    ret.append(from_version(version_));
    ret.append(space);
    ret.append(from_status_code(code_));
    ret.append(space);
    ret.append(to_status_text(code_));
    ret.append(crlf);

    std::unordered_map<std::string, std::string> header_s = headers();
    header_s.emplace(kcontent_type_tag, from_content_type(type_));
    header_s.emplace(kcontent_length_tag, std::to_string(body_.length()));
    for (const auto& [lhs, rhs] : header_s) {
        ret.append(lhs);
        ret.append(": ");
        ret.append(rhs);
        ret.append(crlf);
    }

    ret.append(crlf);

    ret.append(body_);

    return ret;
}

}  // namespace hestina
