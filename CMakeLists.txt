cmake_minimum_required(VERSION 3.20)
project(Infantaria LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(Infantaria
        src/Application.cpp)

target_link_libraries(Infantaria PRIVATE
        glad
        OpenGL::GL
        glfw
)
