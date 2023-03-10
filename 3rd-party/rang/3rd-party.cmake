cmake_minimum_required(VERSION 2.8.12)

project(3rd-party-download)

include(ExternalProject)
ExternalProject_Add(rang
  GIT_REPOSITORY https://github.com/agauniyal/rang.git
  GIT_TAG v3.2
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
