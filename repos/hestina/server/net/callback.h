#pragma once

#include <functional>
#include <memory>

namespace hestina {

class connection;

using new_connection_callback_t =
    std::function<void(std::weak_ptr<connection>)>;
using data_arrive_callback_t =
    std::function<void(std::weak_ptr<connection>, std::string_view data)>;

using connection_close_callback_t =
    std::function<void(std::weak_ptr<connection>)>;
}  // namespace hestina
