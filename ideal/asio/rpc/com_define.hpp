#pragma once

#include <array>
#include <string>

namespace rpc {

namespace detail {

constexpr int kbuffer_size = 1 << 13;
constexpr int khead_length = 4;
constexpr int krequest_id_length = 8;

struct cache_context {
    std::array<char, detail::khead_length> head_length_buff{0};
    std::array<char, detail::krequest_id_length> request_id_length_buff{0};
    std::string body_str;
};

}  // namespace detail
}  // namespace rpc
