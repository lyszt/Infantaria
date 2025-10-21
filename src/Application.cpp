#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utility/utility.h"
#include "shaders/shaders.h"
#include "objects/forms.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

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

    // Ensure viewport is set initially to the window size (callback will handle resizes)
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Impressive. For some reason we need to tell it where the corner of the window is.
    // This + the helper function defines what happens when we resize the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // --- Setup: create shaders and geometry once ---
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram = glCreateProgram();
    renderBasicShaders(&vertexShader, &fragmentShader);
    std::vector<GLuint> shaderList = { vertexShader, fragmentShader };
    attachShaders(shaderProgram, shaderList);
    cleanShaders(shaderList);

    // Check link status
    GLint linkStatus = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus) {
        std::cout << "Shader program linked OK (program id = " << shaderProgram << ")\n";
    } else {
        std::cerr << "Shader program linking failed (program id = " << shaderProgram << ")\n";
    }

    // Create triangle VAO (uploads vertex data and sets attribute pointers)
    unsigned int triangleVAO = make_triangle();
    std::cout << "Created triangle VAO = " << triangleVAO << "\n";


    while (!glfwWindowShouldClose(window)) {
        // Input cmds
        set_esc_quit(window);

        // Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Check and call events, swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Cleanup
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &triangleVAO);

    glfwTerminate();
    return 0;
}