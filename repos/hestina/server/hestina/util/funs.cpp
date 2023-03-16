#include "funs.h"

#include <algorithm>

namespace hestina {
namespace util {

uint64_t ntoh64(uint64_t n) {
    static const int sone = 1;
    static const char sig = *reinterpret_cast<const char*>(&sone);
    if (sig == 0) {
        return n;
    }
    auto* ptr = reinterpret_cast<char*>(&n);
    std::reverse(ptr, ptr + sizeof(uint64_t));
    return n;
}

uint64_t hton64(uint64_t n) {
    return ntoh64(n);
}

}  // namespace util

}  // namespace hestina
