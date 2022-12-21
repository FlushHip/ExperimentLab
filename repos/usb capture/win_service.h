#pragma once

#include <string>

#include <windows.h>
#include <winsvc.h>

#include "utils.h"

namespace hestina {
namespace detail {

class win_service {
public:
    int rigister_service();
    int unrigister_service();

    bool run_service();

private:
    static void set_service_status(DWORD status);
    static void WINAPI service_main(DWORD /*argc*/, LPSTR* /*argv*/);
    static DWORD service_control_handle(DWORD control, DWORD, void*, void*);

private:
    std::string path_{tool::process_path()};
    std::string name_{tool::process_name()};

    static SERVICE_STATUS ssrv_status;
    static SERVICE_STATUS_HANDLE ssrv_status_handle;
};

}  // namespace detail
}  // namespace hestina
