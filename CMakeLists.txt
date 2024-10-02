cmake_minimum_required(VERSION 3.27)
project(life-game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
include_directories(src thirdparty)

add_executable(${PROJECT_NAME} src/life/main.cpp
                               src/lifelib/GameOfLife.h
                               src/lifelib/GameOfLife.cpp
                               src/lifelib/gui.h
                               src/lifelib/gui.cpp)
add_executable(test test/main.cpp
                    test/test_GameOfLife.cpp
                    test/test_gui.cpp
                    src/lifelib/GameOfLife.h
                    src/lifelib/GameOfLife.cpp
                    src/lifelib/gui.h
                    src/lifelib/gui.cpp)


target_link_libraries(${PROJECT_NAME} sfml-graphics)

target_link_libraries(test sfml-graphics)