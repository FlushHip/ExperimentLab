#include "mime_types.hpp"

#include <unordered_map>

namespace http {
namespace server {
namespace mime_types {

std::unordered_map<std::string_view, std::string_view> mappings {
    { "gif", "image/gif" },
};

std::string extension_to_type(std::string_view extension)
{
    if (auto it = mappings.find(extension); it != mappings.end()) {
        return std::string(it->second);
    }
    return "text/plain";
}

}
}
}
