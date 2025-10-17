cmake_minimum_required(VERSION 3.20)
project(Infantaria LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Infantaria
        src/Application.cpp)

target_link_libraries(Infantaria PRIVATE
        OpenGL::GL
        glfw
)

target_include_directories(Infantaria PRIVATE /usr/include)
