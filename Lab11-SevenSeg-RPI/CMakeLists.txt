cmake_minimum_required(VERSION 3.10)

project(SevenSegment C CXX)

# Library
add_library(my_lib
            SHARED 
            src/GPIO.cpp
            src/IOStream.cpp
            src/IStream.cpp
            src/OStream.cpp
            src/Stream.cpp
            src/SevenSegment.cpp)

target_include_directories(my_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Executable
add_executable(${PROJECT_NAME} app/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE my_lib)
