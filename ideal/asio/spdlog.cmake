cmake_minimum_required(VERSION 2.8.12)

project(spdlog-download NONE)

include(ExternalProject)
ExternalProject_Add(spdlog
  GIT_REPOSITORY    https://github.com/gabime/spdlog
  GIT_TAG           v1.10.0
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/spdlog-src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/spdlog-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
