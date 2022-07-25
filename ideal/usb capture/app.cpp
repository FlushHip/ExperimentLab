#include "app.h"

#include <algorithm>
#include <memory>
#include <string>

#pragma warning(push)
#pragma warning(disable : 4101)
#include <argagg/argagg.hpp>
#pragma warning(pop)
#include <thread>

#include "logger.hpp"
#include "usb_cap.h"
#include "websocket_server.h"
#include "win_service.h"

namespace hestina {

struct app::context {
    std::string ip{"127.0.0.1"};
    std::string port{"28168"};
    int filter{1};
    bool is_service{false};

    detail::win_service servicer;

    std::vector<std::shared_ptr<detail::thread_controller>> controllers;
};

app::app() : context_(std::make_unique<context>()) {}

app::~app() {
    std::for_each(context_->controllers.begin(), context_->controllers.end(),
        [](std::shared_ptr<detail::thread_controller> controller) {
            controller->stop();
        });
}

int app::main() {
    LOG_INFO << tool::process_name() << " start. ---------";

    context_->controllers.push_back(
        std::make_shared<detail::usb_cap>(context_->filter));
    context_->controllers.push_back(std::make_shared<detail::websocket_server>(
        context_->ip, context_->port));
    std::for_each(context_->controllers.begin(), context_->controllers.end(),
        [](std::shared_ptr<detail::thread_controller> controller) {
            controller->start();
        });

    using namespace std::literals::chrono_literals;
    for (;;) {
        std::this_thread::sleep_for(1h);
    }

    return 0;
}

int app::init_options(int argc, char** argv) {
    argagg::parser argparser{{
        {"help", {"-h", "--help"}, "shows this help message", 0},
        {"rigister", {"-r", "--rigister"}, "register windows service", 0},
        {"unrigister", {"-u", "--unrigister"}, "unregister windows service", 0},
        {"ip", {"-i", "--ip"}, "ip[x.x.x.x], default: " + context_->ip, 1},
        {"port", {"-p", "--port"}, "port, default: " + context_->port, 1},
        {"filter", {"-f", "--filter"}, "USBCap filter", 1},
        {"service", {"-s", "--service"},
            "run as service(only for sc, don't use this option in dos cmd)", 0},
    }};
    argagg::parser_results args;
    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    if (args["help"]) {
        std::cerr << "Usage: " << tool::process_name() << " [options]"
                  << std::endl
                  << argparser;
        return 0;
    }
    if (args["rigister"]) {
        return rigister_service();
    }
    if (args["unrigister"]) {
        return unrigister_service();
    }
    if (args["ip"]) {
        context_->ip = args["ip"].as<std::string>();
    }
    if (args["port"]) {
        context_->port = args["port"].as<std::string>();
    }
    if (args["filter"]) {
        context_->filter = args["filter"].as<int>();
    }
    if (args["service"]) {
        context_->is_service = true;
    }
    return 1;
}

int app::rigister_service() {
    auto result = context_->servicer.rigister_service();
    (result == 0 ? LOG_INFO : LOG_ERROR)
        << "resister service " << (result == 0 ? "success" : "fail");
    return result;
}

int app::unrigister_service() {
    auto result = context_->servicer.unrigister_service();
    (result == 0 ? LOG_INFO : LOG_ERROR)
        << "unresister service " << (result == 0 ? "success" : "fail");
    return result;
}

int app::run(int argc, char** argv) {
    int result = init_options(argc, argv);
    if (result == 0 || result == -1) {
        return 0;
    }

    if (context_->is_service) {
        LOG_INFO << "run as service";
        context_->servicer.run_service();
    }

    LOG_INFO << "run as normal process";
    return main();
}

}  // namespace hestina
