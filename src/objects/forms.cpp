//
// Created by abensoft on 10/17/25.
//

#include "forms.h"
#include "glad/glad.h"
#include <iostream>

// Once your vertex coordinates have been processed in the vertex shader, they should be in
// normalized device coordinates which is a small space where the x, y and z values vary
// from -1.0 to 1.0.

// The position data of the triangle does not change, is used a lot, and stays the same for every
// render call so its usage type should best be GL_STATIC_DRAW. If, for instance, one would have a
// buffer with data that is likely to change frequently, a usage type of GL_DYNAMIC_DRAW ensures
// the graphics card will place the data in memory that allows for faster writes.

unsigned int make_triangle() {
    float vertices[] = {
        -0.4f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    // This is considering the coordinates of x, y, z
    // I'd suppose every point is a vertex

    // This structure stores vertices into the GPU Memory
    // Sending data to the graphics card from the CPU is
    // relatively slow, so wherever we can we try to send as much data as possible at once.

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO first, then the VBO, upload data, and set the vertex attributes
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data (matches layout(location = 0) in the vertex shader)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind to avoid accidental modification from elsewhere
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}