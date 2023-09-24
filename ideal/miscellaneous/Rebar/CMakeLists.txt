foreach(subdir
    Rebar_L
    Rebar_B
)
    add_subdirectory(${subdir})
endforeach()
