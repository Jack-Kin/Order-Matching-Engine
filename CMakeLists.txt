cmake_minimum_required(VERSION 3.14)

project(OrderMatchingEngine)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)


# Library
file(GLOB_RECURSE SRC_FILES "src/*.hh" "src/*.cc")
add_library(OrderMatcher ${SRC_FILES})
#set_target_properties(OrderMatcher PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}" FOLDER "libraries")
target_include_directories(OrderMatcher PUBLIC "${PROJECT_BINARY_DIR}")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(orderbook test/orderbook_test.cc)

target_link_libraries(orderbook GTest::gtest_main)
target_link_libraries(orderbook OrderMatcher)


include(GoogleTest)
gtest_discover_tests(orderbook)