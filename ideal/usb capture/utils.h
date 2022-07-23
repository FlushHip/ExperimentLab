#pragma once

#include <string>

namespace tool {

using main_handler = int (*)();

std::string process_path();

std::string process_name();

std::string programdata();

int rigister_service();

int unrigister_service();

bool run_service(main_handler fun);

}  // namespace tool
