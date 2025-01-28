project(app)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/app.exe")


find_package(fmt CONFIG REQUIRED)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE fmt::fmt)

find_package(CURL REQUIRED)
target_link_libraries(app PRIVATE CURL::libcurl)

message(STATUS "Executable created at: ${EXE_OUTPUT_PATH}")