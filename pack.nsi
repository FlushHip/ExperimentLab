Name "usb_capture"

OutFile "usb_capture_setup_1.0.6.exe"

RequestExecutionLevel admin

Unicode true

InstallDir $PROGRAMFILES64\usb_capture

Page directory
Page instfiles

Section "Install"
    SetOutPath $INSTDIR

    ExecWait "taskkill /F /IM usb_capture.exe"
    ExecWait "$INSTDIR\usb_capture.exe -u"

    ExecWait "rd /S /Q $INSTDIR"

    File /r "build\install\bin\*"

    ExecWait "$INSTDIR\usb_capture.exe -r"

    ExecWait "net start usb_capture"

SectionEnd
