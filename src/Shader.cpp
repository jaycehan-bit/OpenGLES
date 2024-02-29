#include <fstream>
#include <iostream>
#include <sstream>
#include "glfw3.h"
#include "Shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragShaderFile;
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertexShaderFile.open(vertexPath);
        fragShaderFile.open(fragmentPath);
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragShaderFile.rdbuf();
        vertexShaderFile.close();
        fragShaderFile.close();
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "[Shader] Open code file error" << "\n" << std::endl;
    }
    const char *vertexCharCode = vertexCode.c_str();
    const char *fragCharCode = fragmentCode.c_str();
    std::cout << vertexCharCode << "\n" << fragmentCode << std::endl;
    this->compileShaderProgram(vertexCharCode, fragCharCode);
}

void Shader::useProgram()
{
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::compileShaderProgram(const char *vertexCode, const char *fragmentCode)
{
    int success;
    char log[512];
    // 顶点着色器
    const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, log);
        std::cout << "[Shader] vertex shader compile failed\n" << log << std::endl;
    }
    // 片段着色器
    const unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, log);
        std::cout << "[Shader] fragment shader compile failed\n" << log << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, log);
        std::cout << "[Shader] program link failed\n" << log << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}