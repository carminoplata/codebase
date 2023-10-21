cmake_minimum_required(VERSION 3.14.0)
project(graph VERSION 1.0.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

configure_file(conf/config.h.in config.h @ONLY)

file(GLOB_RECURSE HEADER_FILES inc/*.hpp)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION LESS "10.0.0") OR 
   (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" AND CMAKE_CXX_COMPILER_VERSION LESS "14.0.0"))
  set(gcc ${PROJECT_SOURCE_DIR}/inc/gcc_9)
  message(STATUS "Compiler doesn't support c++20 concepts")
else()
  message(STATUS "Compiler supports c++20 concepts")
  set(gcc ${PROJECT_SOURCE_DIR}/inc/gcc_10)
endif()

include_directories(inc ${gcc})

source_group("Headers" FILES ${HEADER_FILES}) 
source_group("Source Files" FILES ${SOURCE_FILES})


add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}")

#tell to the compiler to use CXX for linking the library
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 

enable_testing()
message(STATUS "Build unit tests for the project. Tests should always be found in the test folder\n")
add_subdirectory(test)