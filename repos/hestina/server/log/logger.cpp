#include "logger.h"

#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>
#include <thread>

namespace hestina {

namespace {

std::string_view level_string(logger::level_t level) {
    static std::string_view sls[]{
        "trace",
        "debug",
        " info",
        " warn",
        "error",
        "fatal",
    };
    return sls[level];
}

std::string date_time_string() {
    auto t_now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(t_now);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
                            t_now - std::chrono::system_clock::from_time_t(t))
                            .count() %
        10000;
    std::ostringstream os;
    os << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S.")
       << microseconds;
    return os.str();
}

std::string thread_id_string() {
    // FIXME (flushhip): id to long
    std::ostringstream os;
    os << std::this_thread::get_id();
    return os.str();
}

}  // namespace

logger::stream::~stream() {
    std::string msg = format();
    if (i_level_ >= logger::instance().level_) {
        logger::instance().write(std::move(msg));
    }
}

std::string logger::stream::format() {
    std::string msg{"["};
    msg += level_string(i_level_);
    msg += "]";

    msg += "[";
    msg += thread_id_string();
    msg += "]";

    msg += "[";
    msg += date_time_string();
    msg += "]";

    msg += "[";
    msg += i_file_;
    msg += ":";
    msg += std::to_string(i_line_);
    msg += ":";
    msg += i_func_;
    msg += "] ";
    msg += str();
    msg += "\n";

    return msg;
}

void logger::init(level_t level,
    std::string_view log_dir,
    std::string_view file_name) {
    level_ = level;

    if (log_dir.empty()) {
        fp_ = stdout;
    } else {
        using namespace std::string_literals;

        // TODO (flushhip): log file name append date

        std::string file_path =
            (std::filesystem::path(log_dir) / file_name).string();

        // TODO (flushhip): log file permissions

        fp_ = std::fopen(file_path.c_str(), "a+");
        if (fp_ == nullptr) {
            std::cerr << "log path " << file_path << " open fail" << std::endl;
            std::exit(-1);
        }
    }

    is_running_ = true;
    thread_ = std::thread([this] { run(); });
}

void logger::uninit() {
    is_running_ = false;
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        while (!queue_.empty()) {
            std::string msg = queue_.front();
            queue_.pop_front();
            flush(std::move(msg));
        }
    }
    if (thread_.joinable()) {
        thread_.join();
    }
    if (fp_ && fp_ != stdout) {
        assert(EOF != std::fclose(fp_));
    }
}

logger::~logger() {
    uninit();
}

void logger::run() {
    while (is_running_) {
        std::string msg;
        {
            // TODO (flushhip): condition_variable
            std::lock_guard<std::mutex> lock(queue_mutex_);
            if (!queue_.empty()) {
                msg = queue_.front();
                queue_.pop_front();
            }
        }
        if (msg.empty()) {
            std::this_thread::yield();
        } else {
            flush(std::move(msg));
        }
    }
}

void logger::flush(std::string&& msg) {
    if (fp_ != nullptr) {
        assert(EOF != std::fputs(msg.c_str(), fp_));
    }
}

void logger::write(std::string&& msg) {
    if (!is_running_) {
        std::cerr << "log thread don't running" << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(queue_mutex_);
    queue_.emplace_back(std::move(msg));
}

}  // namespace hestina
