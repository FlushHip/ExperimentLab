#include "logger.h"

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <filesystem>
#include <future>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string_view>
#include <thread>
#include <utility>
#include <variant>

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
                            .count();
    std::ostringstream os;
    os << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S.")
       << std::setw(6) << std::setfill('0') << microseconds;
    return os.str();
}

std::string thread_id_string() {
    std::ostringstream os;
    os << std::this_thread::get_id();
    return os.str();
}

}  // namespace

struct logger::context {
    context(bool async)
        : async_(async)
        , ctx_(async ? std::variant<async_ctx,
                           sync_ctx>{std::in_place_type<async_ctx>}
                     : std::variant<async_ctx, sync_ctx>{
                           std::in_place_type<sync_ctx>}) {}
    bool async_;
    level_t level_{info};

    struct async_ctx {
        std::mutex queue_mutex_;
        std::condition_variable queue_con_;
        std::deque<std::string> queue_;
        std::thread thread_;
        std::atomic_bool is_running_;
    };

    struct sync_ctx {
        std::mutex flush_mutex_;
    };
    std::variant<async_ctx, sync_ctx> ctx_;
    std::FILE* fp_{nullptr};
};

logger::stream::~stream() {
    std::string msg = format();
    if (i_level_ >= logger::instance().context_->level_) {
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

logger& logger::instance() {
    static logger sinst;
    return sinst;
}

void logger::init(level_t level,
    bool async,
    std::string_view log_dir,
    std::string_view file_name) {
    assert(context_ == nullptr);
    context_ = std::make_unique<context>(async);

    context_->async_ = async;
    if (context_->async_) {
        std::get<context::async_ctx>(context_->ctx_).is_running_ = false;
    }
    context_->level_ = level;

    if (log_dir.empty()) {
        context_->fp_ = stdout;
    } else {
        using namespace std::string_literals;

        // TODO (flushhip): log file name append date

        std::string file_path =
            (std::filesystem::path(log_dir) / file_name).string();

        // TODO (flushhip): log file permissions

        context_->fp_ = std::fopen(file_path.c_str(), "a+");
        if (context_->fp_ == nullptr) {
            std::cerr << "log path " << file_path << " open fail" << std::endl;
            std::exit(-1);
        }
    }

    if (context_->async_) {
        std::get<context::async_ctx>(context_->ctx_).is_running_ = true;
        std::promise<void> pro;
        auto fu = pro.get_future();
        std::get<context::async_ctx>(context_->ctx_).thread_ =
            std::thread([this, pro = std::move(pro)]() mutable {
                pro.set_value();
                run();
            });
        fu.wait();
    }
}

void logger::uninit() {
    if (context_->async_) {
        std::get<context::async_ctx>(context_->ctx_).is_running_ = false;
        std::get<context::async_ctx>(context_->ctx_).queue_con_.notify_one();
        if (std::get<context::async_ctx>(context_->ctx_).thread_.joinable()) {
            std::get<context::async_ctx>(context_->ctx_).thread_.join();
        }
    }
    if (context_->fp_ && context_->fp_ != stdout) {
        assert(EOF != std::fclose(context_->fp_));
    }
}

logger::~logger() {
    uninit();
}

void logger::run() {
    while (true) {
        std::string msg;
        {
            std::unique_lock<std::mutex> lock(
                std::get<context::async_ctx>(context_->ctx_).queue_mutex_);
            std::get<context::async_ctx>(context_->ctx_)
                .queue_con_.wait(lock, [this] {
                    return !std::get<context::async_ctx>(context_->ctx_)
                                .is_running_ ||
                        !std::get<context::async_ctx>(context_->ctx_)
                             .queue_.empty();
                });
            if (!std::get<context::async_ctx>(context_->ctx_).is_running_ &&
                std::get<context::async_ctx>(context_->ctx_).queue_.empty()) {
                break;
            }
            msg = std::get<context::async_ctx>(context_->ctx_).queue_.front();
            std::get<context::async_ctx>(context_->ctx_).queue_.pop_front();
        }
        flush(std::move(msg));
    }
}

void logger::flush(std::string&& msg) {
    if (context_->fp_ != nullptr) {
        assert(EOF != std::fputs(msg.c_str(), context_->fp_));
    }
}

void logger::write(std::string&& msg) {
    if (!context_->async_) {
        std::lock_guard<std::mutex> lock(
            std::get<context::sync_ctx>(context_->ctx_).flush_mutex_);
        flush(std::move(msg));
    } else {
        if (!std::get<context::async_ctx>(context_->ctx_).is_running_) {
            std::cerr << "log thread don't running" << std::endl;
            return;
        }
        {
            std::lock_guard<std::mutex> lock(
                std::get<context::async_ctx>(context_->ctx_).queue_mutex_);
            std::get<context::async_ctx>(context_->ctx_)
                .queue_.emplace_back(std::move(msg));
        }
        std::get<context::async_ctx>(context_->ctx_).queue_con_.notify_one();
    }
}

}  // namespace hestina
