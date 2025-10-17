//
// Created by abensoft on 10/17/25.
//

#include "utility.h"


// Close the program pressing ESC
void setEscQuit(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
