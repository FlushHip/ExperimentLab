#include "buffer.h"

namespace hestina {

void buffer::append(std::string_view data) {
    data_.append(data.begin(), data.end());
}

std::string_view buffer::data() {
    return data_;
}

void buffer::clear() {
    data_.clear();
}

}  // namespace hestina
