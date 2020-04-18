# CMAKELists

cmake_minimum_required (VERSION 2.8.11)
project (sdl-test)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT")


add_executable (sdl-test test.cpp)

target_link_libraries (sdl-test LINK_PUBLIC SDL2 SDL2_ttf SDL2_image)
