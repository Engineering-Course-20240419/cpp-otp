file(GLOB Main_SRCS "*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(core ${Main_SRCS})
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} core)
