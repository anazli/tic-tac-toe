cmake_minimum_required(VERSION 3.22)
project(TicTacToe VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(RUN_DIR ${CMAKE_BINARY_DIR}/bin)
set(EXE tictactoe)
set(CMAKE_DEBUG_POSTFIX d)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SOURCES src/app/application.cpp
            src/app/application.h
            src/gfx/cell.h
            src/gfx/grid.cpp
            src/gfx/grid.h
            src/main/main.cpp
)

add_executable(${EXE} ${SOURCES})
target_include_directories(${EXE} PRIVATE ${PROJECT_SOURCE_DIR}/src)
set_target_properties(${EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUN_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${EXE} PRIVATE "-g")
    set_target_properties(${EXE} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
endif()

target_link_libraries(${EXE} PRIVATE sfml-graphics)
