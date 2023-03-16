#pragma once

#include <string>
#include <string_view>

namespace http {
namespace server {
namespace mime_types {

std::string extension_to_type(std::string_view extension);

}
}
}
