cmake_minimum_required(VERSION 2.8.12)

project(3rd-party-download)

include(ExternalProject)
ExternalProject_Add(nlohmann
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
