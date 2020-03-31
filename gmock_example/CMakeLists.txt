cmake_minimum_required(VERSION 3.17)
project (gmock_example)
 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Locate GTest
find_package(GTest REQUIRED)

#include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(executeTests src/mock_turtle_test.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread gmock)

#include_directories(../ ../vendor/googletest/googletest/include ../vendor/googletest/googlemock/include)
#add_executable(order order.cpp)
#target_link_libraries(order gmock gtest)
