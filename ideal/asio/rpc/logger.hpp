#pragma once

#include <sstream>

#include <spdlog/spdlog.h>

namespace rpc {

class logger : public std::ostringstream {
public:
    logger(const logger&) = delete;
    logger(logger&&) = delete;
    logger& operator=(const logger&) = delete;
    logger&& operator=(logger&&) = delete;

    static void init() {
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s:%# %!] %v");
    }

    explicit logger(spdlog::source_loc&& loc, spdlog::level::level_enum level)
        : loc_(loc), level_(level) {}

    ~logger() override { spdlog::log(loc_, level_, str()); }

private:
    spdlog::source_loc loc_;
    spdlog::level::level_enum level_;
};

}  // namespace rpc

#define LOG_TRACE \
  rpc::logger({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::trace)
#define LOG_DEBUG \
  rpc::logger({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::debug)
#define LOG_INFO \
  rpc::logger({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::info)
#define LOG_WARN \
  rpc::logger({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::warn)
#define LOG_ERROR \
  rpc::logger({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::err)
#define LOG_FATAL \
  rpc::logger({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::critical)
