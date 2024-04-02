cmake_minimum_required(VERSION 2.8.11)
project(cpp_otp)

# CppUTest
include(FetchContent)
FetchContent_Declare(
        CppUTest
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpputest"
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS ON CACHE BOOL "Switch off CppUTest Test build")
set(STDC_WANT_SECURE_LIB OFF CACHE BOOL "Switch off CppUTest Use MSVC safe functions")
#set(MEMORY_LEAK_DETECTION OFF CACHE BOOL "Switch off CppUTest Enable memory leak detection")
FetchContent_MakeAvailable(CppUTest)

add_subdirectory(main)
add_subdirectory(test)
