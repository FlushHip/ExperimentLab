#pragma once

#include <initializer_list>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "utils.h"

namespace hestina {
namespace detail {

class logger : public std::ostringstream {
public:
    logger(const logger&) = delete;
    logger(logger&&) = delete;
    logger& operator=(const logger&) = delete;
    logger&& operator=(logger&&) = delete;

    template <typename... Args>
    static void log(const spdlog::source_loc& loc,
        spdlog::level::level_enum level,
        spdlog::format_string_t<Args...> fmt,
        Args&&... args) {
        internal_logger().log(loc, level, fmt, std::forward<Args>(args)...);
    }

    static std::array<spdlog::sink_ptr, 3> internal_sinks() {
        static auto sconsole_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        static auto sfile_info_sink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                tool::programdata() + "\\" + tool::process_name() +
                "\\logs.txt");
        static auto sfile_dump_sink =
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                tool::programdata() + "\\" + tool::process_name() +
                    "\\dump_data.txt",
                1024 * 1024 * 1, 3);
        return {sconsole_sink, sfile_info_sink, sfile_dump_sink};
    }

    static spdlog::logger& internal_logger() {
        static auto sinks = internal_sinks();
        static spdlog::logger spd_log(
            "multi_sink_log", sinks.begin(), sinks.end());
        return spd_log;
    }

    static void init() {
        auto sinks = internal_sinks();
        sinks[0]->set_level(spdlog::level::info);
        sinks[1]->set_level(spdlog::level::info);
        internal_logger().set_level(spdlog::level::trace);
        internal_logger().set_pattern(
            "[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s:%# %!] %v");
        internal_logger().flush_on(spdlog::level::info);
    }

    explicit logger(spdlog::source_loc&& loc, spdlog::level::level_enum level)
        : loc_(loc), level_(level) {}

    ~logger() override { internal_logger().log(loc_, level_, str()); }

private:
    spdlog::source_loc loc_;
    spdlog::level::level_enum level_;
};

}  // namespace detail
}  // namespace hestina

#define LOG_TRACE          \
  hestina::detail::logger( \
      {__FILE__, __LINE__, __FUNCTION__}, spdlog::level::trace)
#define LOG_DEBUG          \
  hestina::detail::logger( \
      {__FILE__, __LINE__, __FUNCTION__}, spdlog::level::debug)
#define LOG_INFO           \
  hestina::detail::logger( \
      {__FILE__, __LINE__, __FUNCTION__}, spdlog::level::info)
#define LOG_WARN           \
  hestina::detail::logger( \
      {__FILE__, __LINE__, __FUNCTION__}, spdlog::level::warn)
#define LOG_ERROR          \
  hestina::detail::logger( \
      {__FILE__, __LINE__, __FUNCTION__}, spdlog::level::err)
#define LOG_FATAL          \
  hestina::detail::logger( \
      {__FILE__, __LINE__, __FUNCTION__}, spdlog::level::critical)

#define FMT_LOG_TRACE(msg, ...)                                    \
  hestina::detail::logger::log({__FILE__, __LINE__, __FUNCTION__}, \
      spdlog::level::trace, msg, ##__VA_ARGS__);
#define FMT_LOG_DEBUG(msg, ...)                                    \
  hestina::detail::logger::log({__FILE__, __LINE__, __FUNCTION__}, \
      spdlog::level::debug, msg, ##__VA_ARGS__);
#define FMT_LOG_INFO(msg, ...)                                     \
  hestina::detail::logger::log({__FILE__, __LINE__, __FUNCTION__}, \
      spdlog::level::info, msg, ##__VA_ARGS__);
#define FMT_LOG_WARN(msg, ...)                                     \
  hestina::detail::logger::log({__FILE__, __LINE__, __FUNCTION__}, \
      spdlog::level::warn, msg, ##__VA_ARGS__);
#define FMT_LOG_ERROR(msg, ...)                                    \
  hestina::detail::logger::log({__FILE__, __LINE__, __FUNCTION__}, \
      spdlog::level::err, msg, ##__VA_ARGS__);
#define FMT_LOG_FATAL(msg, ...)                                    \
  hestina::detail::logger::log({__FILE__, __LINE__, __FUNCTION__}, \
      spdlog::level::critical, ##__VA_ARGS__);
