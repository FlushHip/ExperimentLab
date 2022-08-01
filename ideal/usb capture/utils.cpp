#pragma once

#include "utils.h"
#include "logger.hpp"

#include <filesystem>
#include <iomanip>
#include <memory>
#include <queue>

#include <windows.h>
#include <winsvc.h>

namespace hestina {
namespace tool {

std::string process_path() {
    DWORD len = 1024;
    std::unique_ptr<wchar_t[]> buffer(new wchar_t[len]);
    GetModuleFileNameW(0, buffer.get(), len);
    while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        len *= 2;
        buffer = std::unique_ptr<wchar_t[]>(new wchar_t[len]);
        GetModuleFileNameW(0, buffer.get(), len);
    }
    return std::filesystem::path(buffer.get()).u8string();
};

std::string process_name() {
    return std::filesystem::u8path(process_path()).stem().u8string();
}

std::string programdata() {
    return std::getenv("programdata");
}

}  // namespace tool
}  // namespace hestina
