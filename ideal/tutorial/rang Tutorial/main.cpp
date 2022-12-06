#include <rang.hpp>

#ifdef WIN32
#  include <windows.h>
#  include <cstdlib>

void BindStdHandlesToConsole() {
    // TODO: Add Error checking.

    // Redirect the CRT standard input, output, and error handles to the console
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);
    freopen("CONOUT$", "w", stdout);

    // Note that there is no CONERR$ file
    HANDLE hStdout = CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hStdin = CreateFile("CONIN$", GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);

    SetStdHandle(STD_OUTPUT_HANDLE, hStdout);
    SetStdHandle(STD_ERROR_HANDLE, hStdout);
    SetStdHandle(STD_INPUT_HANDLE, hStdin);

    // Clear the error state for each of the C++ standard stream objects.
    std::wclog.clear();
    std::clog.clear();
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();
}
#endif

int main() {
#ifdef WIN32
    // I want to create console terminal for GUI application

    // Allocate new console for app:
    AllocConsole();

    // Redirect stderr/stdout/stdin to new console
    BindStdHandlesToConsole();
#endif

    using namespace std;
    using namespace rang;

    // Because rang use static values it means that all redirections should be
    // done before calling rang functions.

    // Visual test for background colors
    cout << bg::green << "This text has green background." << bg::reset << endl
         << bg::red << "This text has red background." << bg::reset << endl
         << bg::black << "This text has black background." << bg::reset << endl
         << bg::yellow << "This text has yellow background." << bg::reset
         << endl
         << bg::blue << "This text has blue background." << bg::reset << endl
         << bg::magenta << "This text has magenta background." << bg::reset
         << endl
         << bg::cyan << "This text has cyan background." << bg::reset << endl
         << bg::gray << fg::black << "This text has gray background."
         << bg::reset << style::reset << endl

         << endl

         // Visual test for foreground colors
         << fg::green << "This text has green color." << fg::reset << endl
         << fg::red << "This text has red color." << fg::reset << endl
         << fg::black << bg::gray << "This text has black color." << fg::reset
         << bg::reset << endl
         << fg::yellow << "This text has yellow color." << fg::reset << endl
         << fg::blue << "This text has blue color." << fg::reset << endl
         << fg::magenta << "This text has magenta color." << fg::reset << endl
         << fg::cyan << "This text has cyan color." << fg::reset << endl
         << fg::gray << "This text has gray color." << style::reset << endl

         << endl

         // Visual test for bright background colors
         << bgB::green << fg::black << "This text has bright green background."
         << style::reset << endl
         << bgB::red << "This text has bright red background." << style::reset
         << endl
         << bgB::black << "This text has bright black background."
         << style::reset << endl
         << bgB::yellow << fg::black
         << "This text has bright yellow background." << style::reset << endl
         << bgB::blue << "This text has bright blue background." << style::reset
         << endl
         << bgB::magenta << "This text has bright magenta background."
         << style::reset << endl
         << bgB::cyan << "This text has bright cyan background." << style::reset
         << endl
         << bgB::gray << fg::black << "This text has bright gray background."
         << style::reset << style::reset << endl

         << endl

         // Visual test for bright foreground colors
         << fgB::green << "This text has bright green color." << endl
         << fgB::red << "This text has bright red color." << endl
         << fgB::black << "This text has bright black color." << endl
         << fgB::yellow << "This text has bright yellow color." << endl
         << fgB::blue << "This text has bright blue color." << endl
         << fgB::magenta << "This text has bright magenta color." << endl
         << fgB::cyan << "This text has bright cyan color." << endl
         << fgB::gray << "This text has bright gray color." << style::reset
         << endl

         << endl

         // Visual test for text effects
         << style::bold << "This text is bold." << style::reset << endl
         << style::dim << "This text is dim." << style::reset << endl
         << style::italic << "This text is italic." << style::reset << endl
         << style::underline << "This text is underlined." << style::reset
         << endl
         << style::blink << "This text text has blink effect." << style::reset
         << endl
         << style::rblink << "This text text has rapid blink effect."
         << style::reset << endl
         << style::reversed << "This text is reversed." << style::reset << endl
         << style::conceal << "This text is concealed." << style::reset << endl
         << style::crossed << "This text is crossed." << style::reset << endl;

    cin.get();

    return 0;
}
