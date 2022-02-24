cmake_minimum_required(VERSION 3.1)
project(UNWORDLER)

file(GLOB src_files src/*.cpp)
file(GLOB header_files src/include/*.h)

add_custom_target(format COMMAND clang-format 
    -style=Google -i ${src_files} ${header_files})

add_custom_target(lint COMMAND clang-tidy -p=${CMAKE_BINARY_DIR} 
    --checks=readability-*,google-* ${src_files} ${header_files})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

execute_process(COMMAND wx-config --cxxflags OUTPUT_VARIABLE UW_CXX_FLAGS)

# UW_CXX_FLAGS has a \n at the end, so remove it by string replace
STRING(REPLACE "\n" " " CMAKE_CXX_FLAGS ${UW_CXX_FLAGS})

execute_process(COMMAND wx-config --libs OUTPUT_VARIABLE UW_LIBS)
set(CMAKE_CXX_STANDARD_LIBRARIES ${UW_LIBS})

include_directories(src/include)
add_executable(UnwordlerApp ${src_files})

