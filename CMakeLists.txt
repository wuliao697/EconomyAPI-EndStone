cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
project(economyAPI CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        endstone
        GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
        GIT_TAG v0.5.4.1
)

FetchContent_MakeAvailable(endstone)

endstone_add_plugin(${PROJECT_NAME} src/economyAPI.cpp)
