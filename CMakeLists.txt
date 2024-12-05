cmake_minimum_required(VERSION 3.25)

project(xmaze)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXAMPLES_PATH ./Examples)
set(SRC_PATH ./Src)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wpedantic")

include_directories(${PROJECT_SOURCE_DIR}/Include)
file(GLOB sources ${SRC_PATH}/*.cpp)
add_library(${PROJECT_NAME} ${sources})

file(GLOB examples ${EXAMPLES_PATH}/*)
foreach(example ${examples})
  get_filename_component(example_name ${example} NAME_WE)
  file(GLOB sources ${example}/*.cpp)
  add_executable(${example_name} ${sources})
  target_link_libraries(${example_name} ${PROJECT_NAME} X11)
endforeach()
