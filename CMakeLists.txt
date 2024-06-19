cmake_minimum_required(VERSION 3.20)
project(Anmex)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR ../../SFML/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

add_executable(Anmex ZadachaPoAnmexy.cpp)

target_link_libraries(Anmex sfml-graphics sfml-audio)
