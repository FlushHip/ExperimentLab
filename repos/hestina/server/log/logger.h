#pragma once

#include <atomic>
#include <deque>
#include <mutex>
#include <ostream>
#include <sstream>
#include <thread>

namespace hestina {
class logger {
public:
    enum level_t {
        trace,
        debug,
        info,
        warn,
        error,
        fatal,
    };
    void init(level_t level,
        std::string_view log_dir = "",
        std::string_view file_name = "");

    void uninit();

    static logger& instance() {
        static logger sinst;
        return sinst;
    }

    class stream : public std::ostringstream {
    public:
        stream(const char* file, int line, const char* func, level_t level)
            : i_file_(file), i_line_(line), i_func_(func), i_level_(level) {}
        ~stream() override;

    private:
        std::string format();

        level_t i_level_;
        const char* i_file_;
        int i_line_;
        const char* i_func_;
    };

private:
    logger() = default;
    ~logger();

    void run();

    void write(std::string&& msg);
    void flush(std::string&& msg);

    level_t level_{info};

    std::mutex queue_mutex_;
    std::deque<std::string> queue_;
    std::thread thread_;
    std::atomic_bool is_running_{false};

    std::FILE* fp_{nullptr};
};
}  // namespace hestina

#define log_trace          \
  hestina::logger::stream( \
      __FILE_NAME__, __LINE__, __FUNCTION__, hestina::logger::trace)
#define log_debug          \
  hestina::logger::stream( \
      __FILE_NAME__, __LINE__, __FUNCTION__, hestina::logger::debug)
#define log_info           \
  hestina::logger::stream( \
      __FILE_NAME__, __LINE__, __FUNCTION__, hestina::logger::info)
#define log_warn           \
  hestina::logger::stream( \
      __FILE_NAME__, __LINE__, __FUNCTION__, hestina::logger::warn)
#define log_fatal          \
  hestina::logger::stream( \
      __FILE_NAME__, __LINE__, __FUNCTION__, hestina::logger::fatal)