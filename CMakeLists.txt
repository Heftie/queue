cmake_minimum_required(VERSION 3.10)
project(queue_project C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Add the main library
add_library(queue STATIC queue.c)

# Specify include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add GoogleTest
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# Add the test executable
add_executable(test_queue test/test_queue.cpp)

# Link the test executable with the main library and GoogleTest
target_link_libraries(test_queue PRIVATE queue gtest gtest_main)

# Enable testing
enable_testing()

# Add a test
add_test(NAME TestQueue COMMAND test_queue)