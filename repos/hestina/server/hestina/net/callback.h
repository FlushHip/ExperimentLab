#pragma once

#include <functional>
#include <memory>
#include <string_view>

namespace hestina {

class connection;
class buffer;

using connection_establish_callback_t =
    std::function<void(std::weak_ptr<connection>)>;
using data_arrive_callback_t =
    std::function<void(std::weak_ptr<connection>, buffer* buff)>;

using connection_close_callback_t =
    std::function<void(std::weak_ptr<connection>)>;
}  // namespace hestina
