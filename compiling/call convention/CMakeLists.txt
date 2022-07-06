add_executable(call_convention main.cpp)

target_compile_options(call_convention
    PRIVATE $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU,ARMClang>:-save-temps=obj -masm=intel>
            $<$<CXX_COMPILER_ID:MSVC>:/Gr>)

set_target_properties(call_convention PROPERTIES FOLDER "advanced compiling")