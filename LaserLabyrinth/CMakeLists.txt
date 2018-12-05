cmake_minimum_required(VERSION 3.12)
project(LaserLabyrinth)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp cmake_modules/MainHero.cpp cmake_modules/MainHero.h
        cmake_modules/Mirror.cpp cmake_modules/Mirror.h
        cmake_modules/GameField.cpp cmake_modules/GameField.h cmake_modules/Transform.cpp cmake_modules/Transform.h cmake_modules/Image.cpp cmake_modules/Image.h cmake_modules/GameObject.cpp cmake_modules/GameObject.h cmake_modules/LaserCannon.cpp cmake_modules/LaserCannon.h cmake_modules/Line.cpp cmake_modules/Line.h cmake_modules/Ray.cpp cmake_modules/Ray.h)

add_executable(LaserLabyrinth ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics network audio)
include_directories("${SFML_INCLUDE_DIR}")
target_link_libraries(LaserLabyrinth ${SFML_LIBRARIES})