cmake_minimum_required(VERSION 3.14.0)
project(SampleApp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
message("SOURCE DIR ${CMAKE_CURRENT_SOURCE_DIR}")
configure_file(conf/config.h.in config.h @ONLY)
file(GLOB_RECURSE HEADER_FILES inc/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

source_group("Headers" FILES ${HEADER_FILES}) 
source_group("Source Files" FILES ${SOURCE_FILES})
include_directories(inc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}")
#tell to the compiler to use CXX for linking the library
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 

enable_testing()
message(STATUS "Build unit tests for the project. Tests should always be found in the test folder\n")
add_subdirectory(test)