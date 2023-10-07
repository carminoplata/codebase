cmake_minimum_required(VERSION 3.14.0)
project(SampleApp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADER_FILES inc/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

source_group("Headers" FILES ${HEADER_FILES}) 
source_group("Source Files" FILES ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#tell to the compiler to use CXX for linking the library
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

enable_testing()
message(STATUS "Build unit tests for the project. Tests should always be found in the test folder\n")
add_subdirectory(test)