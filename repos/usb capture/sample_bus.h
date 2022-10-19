#pragma once

#include <boost/signals2.hpp>

namespace hestina {
namespace detail {

boost::signals2::signal<void(char*, int)>& sample_bus();

}  // namespace detail
}  // namespace hestina
