#include "shaders.h"
#include "glad/glad.h"
#include <filesystem>


    void loadShaderFromSource(const char *filePath, std::string &destination) {
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

    void checkShaderCompile(GLuint shader, std::string &name) {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << name << " shader compilation failed:\n" << infoLog << std::endl;
        }
    }


    std::string getPath(std::string filename)
    {
        std::string currentPath = std::filesystem::current_path();
        std::string shaderPath = currentPath + "/src/shaders/" + filename;
        return shaderPath;
    }

    void renderBasicShaders(GLuint* vertex_shader, GLuint *fragment_shader) {
        std::string vertexShaderSource;
        std::string basicPath = getPath("basic.glsl");
        std::cerr << "[shaders] Loading vertex shader from: " << basicPath << std::endl;
        loadShaderFromSource(basicPath.c_str(), vertexShaderSource);
        std::cerr << "[shaders] Vertex shader source length: " << vertexShaderSource.size() << std::endl;
        // File based (vertex)
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char *vertSourcePtr = vertexShaderSource.c_str();
        glShaderSource(vertexShader, 1, &vertSourcePtr, nullptr);
        glCompileShader(vertexShader);

        std::string vertexName = "Basic vertex shader";
        checkShaderCompile(vertexShader,    vertexName);
        *vertex_shader = vertexShader;


        // Fragment shader
        std::string fragmentShaderSource;
        std::string fragmentPath = getPath("fragment.glsl");
        std::cerr << "[shaders] Loading fragment shader from: " << fragmentPath << std::endl;

        loadShaderFromSource(fragmentPath.c_str(), fragmentShaderSource);
        std::cerr << "[shaders] Fragment shader source length: " << fragmentShaderSource.size() << std::endl;
        // File based (vertex)
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragSourcePtr = fragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &fragSourcePtr, nullptr);
        glCompileShader(fragmentShader);
        std::string fragmentName = "Basic fragment shader";
        checkShaderCompile(fragmentShader, fragmentName);
        *fragment_shader = fragmentShader;
    }



    void attachShaders(GLuint shaderProgram, const std::vector<GLuint>& shaders)
    {
        for (auto shader : shaders) {
            glAttachShader(shaderProgram, shader);
        }
        glLinkProgram(shaderProgram);
        GLint success = 0;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        if(!success) {
            // get and print the info log so the user can see what's wrong
            const int LOG_SIZE = 1024;
            char infoLog[LOG_SIZE];
            glGetProgramInfoLog(shaderProgram, LOG_SIZE, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    void cleanShaders(const std::vector<GLuint>& shaders) {
        for (auto shader : shaders) {
            glDeleteShader(shader);
        }
    }
