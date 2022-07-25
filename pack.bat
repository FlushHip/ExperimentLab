cd %~dp0
if not defined DevEnvDir (
    call "%VCVARSALL_PATH%\vcvarsall.bat" x64
)
if %errorlevel% neq 0 (goto finish)

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S. -Bbuild -G Ninja
if %errorlevel% neq 0 (goto finish)

cmake --build build --target clean
if %errorlevel% neq 0 (goto finish)
if exist "build/install" (rd /S /Q "build/install")
if %errorlevel% neq 0 (goto finish)

cmake --build build --config Debug --target usb_capture --
if %errorlevel% neq 0 (goto finish)
cmake --install build
if %errorlevel% neq 0 (goto finish)

cd %~dp0build
cpack -G ZIP

:finish
cd %~dp0
