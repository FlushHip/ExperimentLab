string(REGEX REPLACE "/$" "" ROOT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ROOT_FOLDER ${ROOT_FOLDER_ABSOLUTE} NAME)

set(programs_cnt_total 0)
set(targets_cnt_total 0)

# add_subdirectory(Interview-17)
# add_subdirectory(Offer)
add_subdirectory(primeval)

message(STATUS)
message(STATUS "\"All ${ROOT_FOLDER}\" <<${programs_cnt_total} programs, ${targets_cnt_total} targets>> generated")
