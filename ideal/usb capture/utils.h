#pragma once

#include <string>

namespace hestina {
namespace tool {

using main_handler = int (*)();

std::string process_path();

std::string process_name();

std::string programdata();

}  // namespace tool
}  // namespace hestina
