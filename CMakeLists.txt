project(app)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/app.exe")

add_executable(app main.cpp)

find_package(fmt CONFIG REQUIRED)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(app PRIVATE fmt::fmt ${OpenCV_LIBS} )

message(STATUS "Executable created at: ${EXE_OUTPUT_PATH}")