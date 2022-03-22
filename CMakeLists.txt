cmake_minimum_required(VERSION 3.10)
project(CppClassesToTypescript)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(CppClassesToTypescript src/main.cpp src/ObjectRegistry.h src/ObjectRegistry.cpp src/ClassDescriptor.h src/Binder.h)
target_include_directories(CppClassesToTypescript PUBLIC include)
target_include_directories(CppClassesToTypescript PRIVATE "external/Catch2/src")

target_link_directories(CppClassesToTypescript PRIVATE "external/Catch2/lib")

target_link_libraries(CppClassesToTypescript
 Catch2$<$<CONFIG:Debug>:d>
 Catch2Main$<$<CONFIG:Debug>:d>
)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/test/target.ts DESTINATION ${CMAKE_CURRENT_LIST_DIR}/Build)
