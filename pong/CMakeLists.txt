cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(pong)

set(FETCHCONTENT_QUIET OFF)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

# Set this to the minimal version you want to support
find_package(raylib 3.7 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    # GIT_REPOSITORY https://github.com/raysan5/raylib.git
    # GIT_TAG 3.7.0
    URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.zip
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

FetchContent_Declare(
  spdlog
  # GIT_REPOSITORY https://github.com/gabime/spdlog.git
  # GIT_TAG        v1.8.5
  URL https://github.com/gabime/spdlog/archive/refs/tags/v1.8.5.zip
)

FetchContent_GetProperties(spdlog)

if(NOT spdlog_POPULATED)
  FetchContent_Populate(spdlog)
  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

# This is the main part:
file(GLOB SRC src/*.cpp src/**/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND cp -r ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${raylib_SOURCE_DIR}/src
  ${spdlog_SOURCE_DIR})

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib spdlog)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# That's it! You should have an example executable that you can run. Have fun!
