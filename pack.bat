cd %~dp0

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S. -Bbuild -G Ninja
if %errorlevel% neq 0 (goto finish)
cmake --build build --config Debug --target usb_capture --
if %errorlevel% neq 0 (goto finish)
cmake --install build
if %errorlevel% neq 0 (goto finish)

cd %~dp0build
cpack -G ZIP

:finish
cd %~dp0
