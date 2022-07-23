#pragma once

#include "utils.h"
#include "logger.hpp"

#include <filesystem>
#include <iomanip>
#include <memory>
#include <queue>

#include <windows.h>
#include <winsvc.h>

namespace tool {

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

namespace {

main_handler proc = nullptr;

SERVICE_STATUS srv_status;
SERVICE_STATUS_HANDLE srv_status_handle;

}  // namespace

std::string process_path() {
    DWORD len = 1024;
    std::unique_ptr<wchar_t[]> buffer(new wchar_t[len]);
    GetModuleFileNameW(0, buffer.get(), len);
    while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        len *= 2;
        buffer = std::unique_ptr<wchar_t[]>(new wchar_t[len]);
        GetModuleFileNameW(0, buffer.get(), len);
    }
    return std::filesystem::path(buffer.get()).u8string();
};

std::string process_name() {
    return std::filesystem::u8path(process_path()).stem().u8string();
}

std::string programdata() {
    return std::getenv("programdata");
}

int rigister_service() {
    std::string path = process_path();
    std::string name = process_name();

    path = "\"" + path + "\"" + " -s";

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

    // description
    SERVICE_DESCRIPTION buff;
    std::string description{
        "Capture usb data, and then transfer usb data by websocket"};
    buff.lpDescription = const_cast<char*>(description.c_str());
    if (!ChangeServiceConfig2(srv_handler, SERVICE_CONFIG_DESCRIPTION, &buff)) {
        LOG_FATAL << "can't write service description, error code : "
                  << GetLastError();
        return -1;
    }

    /*
    // dependencies
    std::string depend_service = "USBPcap\0";
    if (!ChangeServiceConfig(srv_handler, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE,
            SERVICE_NO_CHANGE, nullptr, nullptr, nullptr,
            depend_service.c_str(), nullptr, nullptr, nullptr)) {
        LOG_FATAL << "can't write service depend_service " << depend_service
                  << " , error code : " << GetLastError();
        return -1;
    }
    */
    return 0;
}

int unrigister_service() {
    std::string name = process_name();

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
    SERVICE_STATUS status = {0};
    if (ControlService(srv_handler, SERVICE_CONTROL_STOP, &status)) {
        while (QueryServiceStatus(srv_handler, &status)) {
            if (status.dwCurrentState != SERVICE_STOP_PENDING) {
                break;
            }
        }
        if (status.dwCurrentState != SERVICE_STOPPED) {
            LOG_ERROR << "can't stop servide";
        }
    }
    if (!DeleteService(srv_handler)) {
        LOG_FATAL << "can't delete service, error code : " << GetLastError();
        return -1;
    }
    return 0;
}

void set_service_status(DWORD status) {
    srv_status.dwCurrentState = status;

    SetServiceStatus(srv_status_handle, &srv_status);
}

DWORD service_control_handle(DWORD control, DWORD, void*, void*) {
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

void WINAPI service_main(DWORD /*argc*/, LPSTR* /*argv*/) {
    srv_status_handle =
        RegisterServiceCtrlHandlerEx("", service_control_handle, nullptr);
    if (!srv_status_handle) {
        LOG_FATAL << "rigister service control handle fail, error code : "
                  << GetLastError();
        return;
    }

    // init
    srv_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    srv_status.dwWin32ExitCode = 0;
    srv_status.dwServiceSpecificExitCode = 0;
    srv_status.dwCheckPoint = 0;
    srv_status.dwWaitHint = 0;
    srv_status.dwControlsAccepted = SERVICE_ACCEPT_STOP |
        SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE |
        SERVICE_ACCEPT_PRESHUTDOWN | SERVICE_ACCEPT_SESSIONCHANGE;
    set_service_status(SERVICE_START_PENDING);

    set_service_status(SERVICE_RUNNING);
    proc();
    set_service_status(SERVICE_STOPPED);
}

bool run_service(main_handler fun) {
    proc = fun;
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

}  // namespace tool
