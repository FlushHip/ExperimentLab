#pragma once

#include <string_view>

namespace hestina {

enum class method_t {
    kinvalid,
    kget,
    kpost,
    khead,
    kput,
    kdelete,
};

std::string_view from_method(method_t method);
method_t to_method(std::string_view method);

enum class version_t {
    kunknow,
    khttp10,
    khttp11,
};

std::string_view from_version(version_t version);
version_t to_version(std::string_view version);

enum class status_code_t {
    kok = 200,
    knot_find = 404,
};

std::string from_status_code(status_code_t code);
status_code_t to_status_code(std::string_view code);

std::string_view to_status_text(status_code_t code);

constexpr const std::string_view kcontent_length_tag = "Content-Length";
constexpr const std::string_view kcontent_type_tag = "Content-Type";
constexpr const std::string_view kconnection = "Connection";
constexpr const std::string_view kconnection_close = "close";
constexpr const std::string_view kconnection_keep_alive = "keep-alive";

enum class content_type_t {
    knone = 0,
    ktext_plain,
    ktext_html,
    kapplication_json,
};

std::string_view from_content_type(content_type_t type);
content_type_t to_content_type(std::string_view type);

}  // namespace hestina
