#include "sample_bus.h"

namespace hestina {
namespace detail {

boost::signals2::signal<void(char*, int)>& sample_bus() {
    static boost::signals2::signal<void(char*, int)> sbus;
    return sbus;
}

}  // namespace detail
}  // namespace hestina
