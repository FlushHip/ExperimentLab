cmake_minimum_required(VERSION 2.8.12)

project(3rd-party-download)

include(ExternalProject)
ExternalProject_Add(doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.9
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
