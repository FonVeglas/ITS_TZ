cmake_minimum_required(VERSION 3.19)
project(ITS_TZ)

set(CMAKE_CXX_STANDARD 17)

set(CURL_ROOT E:/Programming/Projects/C++/libs/curl-7.78.0-win64-mingw)
add_definitions(-DCURL_STATICLIB)
FIND_PACKAGE(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

if(NOT CURL_FOUND)
    message(FATAL_ERROR "CURL NOT FOUND: " ${CURL_ROOT} )
endif()
message(${CURL_INCLUDE_DIRS})
message(${CURL_LIBRARIES})
message(${CURL_VERSION_STRING})


set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(ITS_TZ main.cpp)
target_link_libraries(ITS_TZ ${CURL_LIBRARIES})

