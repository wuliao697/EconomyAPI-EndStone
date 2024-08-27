cmake_minimum_required(VERSION 3.15)
project(EconomyAPI)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
        endstone
        GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
        GIT_TAG main
)
FetchContent_Declare(
        rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG master
)

FetchContent_MakeAvailable(endstone rapidjson)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fPIC")
    link_libraries(-static-libgcc -static-libstdc++ libc++.a libc++abi.a)
endif ()

endstone_add_plugin(${PROJECT_NAME} src/economyAPI.cpp)
