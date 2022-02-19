cmake_minimum_required(VERSION 3.0)
project(UNWORDLER)
include_directories(src/include)
file(GLOB src_files src/*.cpp)
add_executable(UnwordlerApp ${src_files})

