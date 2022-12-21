#include <hestina/log/logger.h>

int main() {
    hestina::logger::instance().init(hestina::logger::finer, true);

    log_finer << "log.....";
    log_trace << "log.....";
    log_debug << "log.....";
    log_info << "log.....";
    log_warn << "log.....";
    log_error << "log.....";
    log_fatal << "log.....";

    return 0;
}
