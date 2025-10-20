#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "glad/glad.h"

#ifndef INFANTARIA_SHADERS_H
#define INFANTARIA_SHADERS_H


class shaders {
};

void loadShaderFromSource(const char *filePath, std::string &destination);
void renderBasicShaders(GLuint* vertex_shader, GLuint* fragment_shader);
void attachShaders(GLuint shaderProgram, const std::vector<GLuint> &shaders);
void cleanShaders(const std::vector<GLuint>& shaders);

#endif //INFANTARIA_SHADERS_H