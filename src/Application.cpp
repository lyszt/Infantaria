#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 720

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}


int main()
{
    glfwInit();



    // Really cool. This sets OpenGl to version 3.3
    // as you could see in the book you read, this chooses the core profile
    // and makes sure we aren't using 4.6 instead
    // You can probably do other things using glfwWindowHint concerning the application project / settings overall


    //  Telling GLFW we want to use the core-profile means we’ll get access to a
    // smaller subset of OpenGL features without backwards-compatible features we no longer need.
    // Stuff from 1999 lol

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Infantaria: Regressus Regis", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW Window." << "\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD." << "\n";
        return -1;
    }

    // Impressive. For some reason we need to tell it where the corner of the window is.
    // This + the helper function defines what happens when we resize the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}