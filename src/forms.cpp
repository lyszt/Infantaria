//
// Created by abensoft on 10/17/25.
//

#include "forms.h"

#include "glad/glad.h"

// Once your vertex coordinates have been processed in the vertex shader, they should be in
// normalized device coordinates which is a small space where the x, y and z values vary
// from -1.0 to 1.0.

// The position data of the triangle does not change, is used a lot, and stays the same for every
// render call so its usage type should best be GL_STATIC_DRAW. If, for instance, one would have a
// buffer with data that is likely to change frequently, a usage type of GL_DYNAMIC_DRAW ensures
// the graphics card will place the data in memory that allows for faster writes.

void make_triangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    // This is considering the coordinates of x, y, z
    // I'd suppose every point is a vertex

    // This structure stores vertices into the GPU Memory
    // Sending data to the graphics card from the CPU is
    // relatively slow, so wherever we can we try to send as much data as possible at once.

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}