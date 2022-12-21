#pragma once

#include <string>

namespace hestina {

class buffer {
public:
    void append(std::string_view data);
    std::string_view data();
    void clear();

private:
    std::string data_;
};

}  // namespace hestina
