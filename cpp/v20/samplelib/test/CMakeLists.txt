cmake_minimum_required(VERSION 3.14.0)
project(GraphUnitTests VERSION 1.0.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
message(STATUS "Compiles using GCC ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(gcc_9 ${PROJECT_SOURCE_DIR}/../inc/gcc_9)
set(gcc_10 ${PROJECT_SOURCE_DIR}/../inc/gcc_10)
cmake_policy(SET CMP0135 NEW)

include_directories(../inc inc 
  $<$<VERSION_LESS:$<CXX_COMPILER_VERSION>,10>:${gcc_9}>
  $<$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,10>:${gcc_10}>)

# Download GTest and integrate it
include(FetchContent)

FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)

file(GLOB_RECURSE PROJ_TO_TEST_H ../inc/*.hpp)
file(GLOB_RECURSE PROJ_TO_TEST_CPP ../src/*.cpp)
file(GLOB_RECURSE HEADER_FILES inc/*.hpp)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

source_group("Headers" FILES ${HEADER_FILES}) 
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Project Target Header Files" FILES ${PROJ_TO_TEST_H}) 
source_group("Project Target Source Files" FILES ${PROJ_TO_TEST_CPP})

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${PROJ_TO_TEST_H}
               ${PROJ_TO_TEST_CPP})
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10)
  message("Enable concepts: List features  ${CMAKE_CXX_COMPILE_FEATURES} ")
  #target_compile_features(${PROJECT_NAME} PRIVATE concepts)
endif()
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
add_test(NAME runUnitTests COMMAND runTests)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})