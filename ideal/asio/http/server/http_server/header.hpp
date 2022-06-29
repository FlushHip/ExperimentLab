#pragma once

#include <string>

namespace http {
namespace server {

struct Header
{
    std::string name;
    std::string value;
};

}
}
