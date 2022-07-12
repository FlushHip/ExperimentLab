#include "lib.h"

namespace lib_static {
namespace a {

int global_i = 0;
int& static_var() {
    static int i = 0;
    return i;
}

int& global_var() {
    return global_i;
}

}  // namespace a
}  // namespace lib_static
