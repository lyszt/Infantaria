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
        src/Application.cpp
        src/utility.cpp
        src/utility.h
        src/forms.cpp
        src/forms.h)

target_link_libraries(Infantaria PRIVATE
        glad
        OpenGL::GL
        glfw
)

if(NOT TARGET OpenGL::GL)
    find_library(GL_LIB NAMES GL libGL)
    if(GL_LIB)
        message(STATUS "Linking explicit GL library: ${GL_LIB}")
        target_link_libraries(Infantaria PRIVATE ${GL_LIB})
    else()
        message(WARNING "OpenGL::GL target not found and libGL not located. On Linux, install Mesa/NVIDIA/AMD GL dev packages (e.g. libgl1-mesa-dev) to provide libGL.so.")
    endif()
endif()

