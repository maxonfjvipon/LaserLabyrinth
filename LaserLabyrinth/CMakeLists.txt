cmake_minimum_required(VERSION 3.12)
project(LaserLabyrinth)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp cmake_modules/MainHero.cpp cmake_modules/MainHero.h cmake_modules/Mirror.cpp cmake_modules/Mirror.h cmake_modules/Picture.cpp cmake_modules/Picture.h)

add_executable(LaserLabyrinth ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED system window graphics network audio)
include_directories("${SFML_INCLUDE_DIR}")
target_link_libraries(LaserLabyrinth ${SFML_LIBRARIES})