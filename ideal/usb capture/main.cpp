#include <iostream>
#include <string_view>
#include <thread>

#include "usb_cap/usb_cap.h"

void handle_capture(char* data, int len) {
    if (len > 100)
        std::cout << "len : " << len << std::endl;
    // std::cout << std::endl;
}

int main(int argc, char** argv) {
    Init();
    // 3,
    if (SetFilter(3) < 0) {
        std::cerr << "set filter fail" << std::endl;
        return -1;
    }
    StartCapture(handle_capture);

    return 0;
}
