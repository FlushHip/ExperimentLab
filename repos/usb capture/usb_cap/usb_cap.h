#pragma once

#define USBCAP_IMPORT __declspec(dllimport)

extern "C" {

void USBCAP_IMPORT Init();

int USBCAP_IMPORT SetFilter(int i);

int StartCapture(void (*callback)(char* data, int len));

void USBCAP_IMPORT StopCapture();

void USBCAP_IMPORT Clear();
}
