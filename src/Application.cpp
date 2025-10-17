#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    glfwInit();

    // Really cool. This sets OpenGl to version 3.3
    // as you could see in the book you read, this choses the core profile
    // and makes sure we aren't using 4.6 instead
    // You can probably do other things using glfwWindowHint concerning the application project / settings overall


    //  Telling GLFW we want to use the core-profile means we’ll get access to a
    // smaller subset of OpenGL features without backwards-compatible features we no longer need.
    // Stuff from 1999 lol

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glfwTerminate();
    return 0;
}