//
// Created by abensoft on 10/17/25.
//

#include "shaders.h"

#include "glad/glad.h"


void loadShaderFromSource(const char *filePath, std::string destination) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        destination = "";
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    destination = buffer.str();

}

void checkShaderCompile(GLuint shader, const std::string &name) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << name << " shader compilation failed:\n" << infoLog << std::endl;
    }
}


void renderBasicShaders(GLuint* vertex_shader, GLuint *fragment_shader) {
    std::string vertexShaderSource;
    loadShaderFromSource("shaders/basic.glsl", vertexShaderSource);
    // File based (vertex)
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertSourcePtr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertSourcePtr, nullptr);
    glCompileShader(vertexShader);

    checkShaderCompile(vertexShader, "Basic vertex shader");
    *vertex_shader = vertexShader;


    // Fragment shader
    const std::string fragmentShaderSource;
    loadShaderFromSource("shaders/fragment.glsl", fragmentShaderSource);
    // File based (vertex)

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragSourcePtr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragSourcePtr, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompile(fragmentShader, "Basic fragment shader");
    *fragment_shader = fragmentShader;
}



void attachShaders(GLuint shaderProgram, const std::vector<GLuint>& shaders) {
    for (auto shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
}
