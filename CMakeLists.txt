cmake_minimum_required(VERSION 3.10)

project(myGame)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(myGame main.cpp ${SOURCES})


set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/SFML/include")
set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/external/SFML/lib")


include_directories(${SFML_INCLUDE_DIR})


link_directories(${SFML_LIBRARY_DIR})


target_link_libraries(myGame
    ${SFML_LIBRARY_DIR}/libsfml-graphics.dylib
    ${SFML_LIBRARY_DIR}/libsfml-window.dylib
    ${SFML_LIBRARY_DIR}/libsfml-system.dylib
)

# Включение дополнительных флагов компиляции (например, -Wall и -pedantic)
# target_compile_options(myGame PRIVATE -Wall -Wextra -pedantic)
