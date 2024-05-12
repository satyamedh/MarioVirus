cmake_minimum_required(VERSION 3.28)
project(MarioVirus)

set(CMAKE_CXX_STANDARD 17)

# Specify the manifest file in the add_executable command
add_executable(MarioVirus main.cpp MarioVirus.manifest)

# Specify the static library
target_link_libraries(MarioVirus winmm)

# Add static link flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static -lpthread")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/videoo.mpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})