set(Test_SRCS AllTests.cpp BirthdayTest.cc)

add_executable(cpp_otp_test ${Test_SRCS})

include_directories(${CMAKE_SOURCE_DIR}/main)
include_directories(${CMAKE_SOURCE_DIR}/cpputest)
include_directories(${CMAKE_SOURCE_DIR}/cpputest/include)
include_directories(${CMAKE_SOURCE_DIR}/cpputest/include/Platforms/Gcc)
link_directories(${CMAKE_SOURCE_DIR}/cpputest/lib)
target_link_libraries(cpp_otp_test PRIVATE core CppUTest CppUTestExt)
