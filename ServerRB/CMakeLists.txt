cmake_minimum_required(VERSION 3.10)
project(ServerRB)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
)
FetchContent_MakeAvailable(rapidjson)
include_directories(${rapidjson_SOURCE_DIR}/include)

add_executable(ServerRB src/main.cpp src/Server.cpp src/Algorithm.cpp)

target_include_directories(ServerRB PUBLIC inc)

target_link_libraries(ServerRB ${OpenCV_LIBS} httplib)
