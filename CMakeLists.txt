cmake_minimum_required(VERSION 3.10)
project(challenge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(challenge src/main.cpp)
target_include_directories(challenge PUBLIC include)
target_include_directories(challenge PRIVATE "external/Catch2/src")

target_link_directories(challenge PRIVATE "external/Catch2/lib")

target_link_libraries(challenge
 Catch2$<$<CONFIG:Debug>:d>
 Catch2Main$<$<CONFIG:Debug>:d>
)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/target.ts DESTINATION ${CMAKE_CURRENT_LIST_DIR}/Build)
