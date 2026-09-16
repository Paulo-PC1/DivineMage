cmake_minimum_required(VERSION 3.20)

project(DivineMage VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(raylib nlohmann_json)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(DivineMage ${PROJECT_SOURCES})   

target_include_directories(DivineMage PRIVATE include)
target_link_libraries(DivineMage PRIVATE raylib nlohmann_json::nlohmann_json)

target_compile_definitions(DivineMage PRIVATE
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)