#include "http_common.h"

#include <hestina/log/logger.h>

#include <cassert>
#include <string>
#include <string_view>
#include <unordered_map>

namespace hestina {

std::string_view from_method(method_t method) {
    static std::unordered_map<method_t, std::string_view> sstring_method{
        {method_t::kinvalid, "INVALID"},
        {method_t::kget, "GET"},
        {method_t::kpost, "POST"},
        {method_t::khead, "HEAD"},
        {method_t::kput, "PUT"},
        {method_t::kdelete, "DELETE"},
    };
    assert(sstring_method.contains(method));
    return sstring_method[method];
}

method_t to_method(std::string_view method) {
    static std::unordered_map<std::string_view, method_t> senum_method{
        {"GET", method_t::kget},
        {"POST", method_t::kpost},
        {"HEAD", method_t::khead},
        {"PUT", method_t::kput},
        {"DELETE", method_t::kdelete},
    };
    assert(senum_method.contains(method));
    return senum_method[method];
}

std::string_view from_version(version_t version) {
    static std::unordered_map<version_t, std::string_view> sstring_version{
        {version_t::kunknow, "UNKNOWN"},
        {version_t::khttp10, "HTTP/1.0"},
        {version_t::khttp11, "HTTP/1.1"},
    };
    assert(sstring_version.contains(version));
    return sstring_version[version];
}

version_t to_version(std::string_view version) {
    static std::unordered_map<std::string_view, version_t> senum_version{
        {"HTTP/1.0", version_t::khttp10},
        {"HTTP/1.1", version_t::khttp11},
    };
    assert(senum_version.contains(version));
    return senum_version[version];
}

std::string from_status_code(status_code_t code) {
    return std::to_string(static_cast<int>(code));
}

status_code_t to_status_code(std::string_view code) {
    return static_cast<status_code_t>(std::stoi(std::string(code)));
}

std::string_view to_status_text(status_code_t code) {
    static std::unordered_map<status_code_t, std::string_view> sstring_status{
        {status_code_t::kok, "OK"},
        {status_code_t::knot_find, "Not Found"},
    };
    assert(sstring_status.contains(code));
    return sstring_status[code];
}

std::string_view from_content_type(content_type_t type) {
    static std::unordered_map<content_type_t, std::string_view>
        sstring_content_type{
            {content_type_t::knone, "none"},
            {content_type_t::kapplication_json, "application/json"},
            {content_type_t::ktext_plain, "text/plain"},
            {content_type_t::ktext_html, "text/html"},
        };
    assert(sstring_content_type.contains(type));
    return sstring_content_type[type];
}

content_type_t to_content_type(std::string_view type) {
    static std::unordered_map<std::string_view, content_type_t>
        senum_content_type{
            {"none", content_type_t::knone},
            {"application/json", content_type_t::kapplication_json},
            {"text/plain", content_type_t::ktext_plain},
            {"text/html", content_type_t::ktext_html},
        };
    assert(senum_content_type.contains(type));
    return senum_content_type[type];
}

}  // namespace hestina
