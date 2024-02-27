#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>

class Shader
{
private:
    void compileShaderProgram(const char *vertexCode, const char *fragmentCode);

public:
    // 程序ID
    unsigned int ID;
    // 构造方法
    // @param vertexPath 顶点着色器文件路径
    // @param fragmentPath 片段着色器文件路径
    Shader(const char *vertexPath, const char *fragmentPath);
    void userProgram();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif