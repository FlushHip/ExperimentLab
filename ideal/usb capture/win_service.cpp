#include "win_service.h"

#include "app.h"
#include "logger.hpp"

namespace hestina {
namespace detail {

namespace raii {

class win_service_handle {
public:
    win_service_handle(SC_HANDLE handler) : handler_(handler) {}
    ~win_service_handle() { CloseServiceHandle(handler_); }

    operator SC_HANDLE() { return handler_; }

private:
    SC_HANDLE handler_;
};

}  // namespace raii

SERVICE_STATUS win_service::ssrv_status;
SERVICE_STATUS_HANDLE win_service::ssrv_status_handle;

int win_service::rigister_service() {
    auto name = name_;
    auto path = "\"" + path_ + "\"" + " -s";

    raii::win_service_handle scm_handler = OpenSCManager(
        nullptr, nullptr, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
    if (!scm_handler) {
        LOG_FATAL << "can't open service manager, error code : "
                  << GetLastError();
        return -1;
    }
    raii::win_service_handle srv_handler = CreateService(scm_handler,
        name.c_str(), name.c_str(), SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
        path.c_str(), nullptr, nullptr, nullptr, nullptr, nullptr);
    if (!srv_handler) {
        LOG_FATAL << "can't create service, error code : " << GetLastError();
        return -1;
    }

    SERVICE_DESCRIPTION buff;
    std::string description{
        "Capture usb data, and then transfer usb data by websocket"};
    buff.lpDescription = const_cast<char*>(description.c_str());
    if (!ChangeServiceConfig2(srv_handler, SERVICE_CONFIG_DESCRIPTION, &buff)) {
        LOG_FATAL << "can't write service description, error code : "
                  << GetLastError();
        return -1;
    }

#if false
    std::string depend_service = "USBPcap\0";
    if (!ChangeServiceConfig(srv_handler, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE,
            SERVICE_NO_CHANGE, nullptr, nullptr, nullptr,
            depend_service.c_str(), nullptr, nullptr, nullptr)) {
        LOG_FATAL << "can't write service depend_service " << depend_service
                  << " , error code : " << GetLastError();
        return -1;
    }
#endif
    return 0;
}

int win_service::unrigister_service() {
    auto name = name_;
    raii::win_service_handle scm_handler =
        OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scm_handler) {
        LOG_FATAL << "can't open service manager, error code : "
                  << GetLastError();
        return -1;
    }
    raii::win_service_handle srv_handler =
        OpenService(scm_handler, name.c_str(), SERVICE_STOP | DELETE);
    if (!srv_handler) {
        LOG_FATAL << "can't open service, error code : " << GetLastError();
        return -1;
    }
    if (ControlService(srv_handler, SERVICE_CONTROL_STOP, &ssrv_status)) {
        while (QueryServiceStatus(srv_handler, &ssrv_status)) {
            if (ssrv_status.dwCurrentState != SERVICE_STOP_PENDING) {
                break;
            }
        }
        if (ssrv_status.dwCurrentState != SERVICE_STOPPED) {
            LOG_ERROR << "can't stop servide";
        }
    }
    if (!DeleteService(srv_handler)) {
        LOG_FATAL << "can't delete service, error code : " << GetLastError();
        return -1;
    }
    return 0;
}

void win_service::set_service_status(DWORD status) {
    ssrv_status.dwCurrentState = status;

    SetServiceStatus(ssrv_status_handle, &ssrv_status);
}

DWORD win_service::service_control_handle(DWORD control, DWORD, void*, void*) {
    switch (control) {
        case SERVICE_CONTROL_STOP:
            set_service_status(SERVICE_STOP_PENDING);
            LOG_INFO << tool::process_name() << " stop";
            set_service_status(SERVICE_STOPPED);
            break;
        case SERVICE_CONTROL_PAUSE:
            set_service_status(SERVICE_PAUSE_PENDING);
            LOG_INFO << tool::process_name() << " pause";
            set_service_status(SERVICE_PAUSED);
            break;
        case SERVICE_CONTROL_CONTINUE:
            set_service_status(SERVICE_CONTINUE_PENDING);
            LOG_INFO << tool::process_name() << " continue";
            set_service_status(SERVICE_RUNNING);
            break;
        case SERVICE_CONTROL_SHUTDOWN:
            LOG_INFO << tool::process_name() << " shutdown";
            set_service_status(SERVICE_STOPPED);
            break;
        default:
            LOG_INFO << tool::process_name() << " other control : " << control;
            break;
    }
    return 0;
}

void WINAPI win_service::service_main(DWORD /*argc*/, LPSTR* /*argv*/) {
    ssrv_status_handle =
        RegisterServiceCtrlHandlerEx("", service_control_handle, nullptr);
    if (!ssrv_status_handle) {
        LOG_FATAL << "rigister service control handle fail, error code : "
                  << GetLastError();
        return;
    }

    // init
    ssrv_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ssrv_status.dwWin32ExitCode = 0;
    ssrv_status.dwServiceSpecificExitCode = 0;
    ssrv_status.dwCheckPoint = 0;
    ssrv_status.dwWaitHint = 0;
    ssrv_status.dwControlsAccepted = SERVICE_ACCEPT_STOP |
        SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE |
        SERVICE_ACCEPT_PRESHUTDOWN | SERVICE_ACCEPT_SESSIONCHANGE;
    set_service_status(SERVICE_START_PENDING);

    set_service_status(SERVICE_RUNNING);
    app::get().main();
    set_service_status(SERVICE_STOPPED);
}

bool win_service::run_service() {
    std::string name = tool::process_name();
    SERVICE_TABLE_ENTRY svcDispatchTable[] = {
        {const_cast<char*>(name.c_str()), service_main},
        {nullptr, nullptr},
    };
    if (!StartServiceCtrlDispatcher(svcDispatchTable)) {
        LOG_FATAL << "start service control dispatcher fail, error code : "
                  << GetLastError();
        return false;
    }
    return true;
}

}  // namespace detail
}  // namespace hestina
