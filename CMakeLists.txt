cmake_minimum_required(VERSION 3.5.0)
project(ASS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_LINK_LIBS -lm -lGL -lGLU -lGLEW -lSDL2main -lSDL2 -lSDL2_image)

link_directories(/usr/local/lib)

add_definitions(-g -std=c++14 -Wfatal-errors)

include_directories(src)

file(GLOB src0 "src/*.cpp")

add_executable(out
    ${src0}
)
target_link_libraries(out ${PROJECT_LINK_LIBS})
