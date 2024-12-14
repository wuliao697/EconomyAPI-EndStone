cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE Release)
project(economyAPI CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES "src/endstone/*" "pyproject.toml")

include(FetchContent)
FetchContent_Declare(
        endstone
        GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
        GIT_TAG v0.5.6)

FetchContent_MakeAvailable(endstone)

endstone_add_plugin(${PROJECT_NAME} src/economyAPI.cpp)
