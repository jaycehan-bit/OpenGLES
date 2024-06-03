#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "glad.h"
#include "glfw3.h"
#include "Shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLFWwindow *initWindow();
unsigned int generateTexture(const std::string imageName);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{   
    GLFWwindow *window = initWindow();
    const char *vertexShaderPath = "/Users/jaycehan/Project/Jayce/OpenGL/src/Shaders/VertexShader.vs";
    const char *fragShaderPath = "/Users/jaycehan/Project/Jayce/OpenGL/src/Shaders/FragmentShader.fs";
    Shader shader(vertexShaderPath, fragShaderPath);
    shader.useProgram();
    // 设置窗户位置大小
    // 前两个参数控制窗口左下角位置；后两个参数表示渲染窗口的宽高，以像素为单位。
    glViewport(0, 0, 800, 600);

    // 定义顶点坐标
    const float vertices[] = {
        // 坐标              // 颜色                                // 纹理坐标
        // 左上角
        -0.5, 0.5, 0.0,     254/255.0, 67/255.0, 101/255.0,         0.0, 0.0,
        // 右上角
        0.5, 0.5, 0.0,      252/255.0, 157/255.0, 154/255.0,        1.0, 0.0,
        // 右下角  
        0.5, -0.5, 0.0,     249/255.0, 205/255.0, 173/255.0,        1.0, 1.0,
        // 左下角
        -0.5, -0.5, 0.0,    1.0,       245/255.0, 247/255.0,        0.0, 1.0,
    };

    const unsigned int indices[] = {
        0, 1, 2,    // 第一个三角形顶点坐标
        0, 2, 3,    // 第二个三角形顶点坐标
    };

    // TODO: 修改为相对路径
    std::string imageName = "/Users/jaycehan/Project/Jayce/OpenGL/src/Source/MissFortune.jpg";
    const unsigned int texture = generateTexture(imageName);
    std::cout << "texture: " << texture << std::endl;

    std::string imageTwoName = "/Users/jaycehan/Project/Jayce/OpenGL/src/Source/Sunset.jpg";
    glActiveTexture(GL_TEXTURE1);
    const unsigned int sunSetTexture = generateTexture(imageTwoName);
    std::cout << "sunSetTexture: " << sunSetTexture << std::endl;

    // 定义生成VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 定义生成VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // 将VBO绑定OpenGL上下文
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将顶点数据复制到VBO中供OpenGL使用
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 定义生成EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /**
     * 告诉OpenGL如何解析顶点数据
     * @param 0: 需要配置的顶点属性。对应location=0，把顶点数据传入到position这个属性中
     * @param 1: 指定顶点属性的大小。顶点属性是vec3，有三个值组成
     * @param 2: 顶点数据结构。指定为float
     * @param 3: 是否标准化数据。所有数据都被映射到0-1之间
     * @param 4: 步长。告诉OpenGL在连续顶点属性组之间的间隔
     * @param 5: 位置数据在缓冲中起始位置的偏移量
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 如何解析纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 告诉OpenGL每个着色器采样器属于哪个纹理单元
    // 给Uniform赋值前必须useProgram
    shader.useProgram();
    // glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    // glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);
    // 或者使用着色器类设置
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        // 设置清屏后的颜色
        glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
        // 清屏
        glClear(GL_COLOR_BUFFER_BIT);
        // 启用着色器程序
        shader.useProgram();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, sunSetTexture);

        glBindVertexArray(VAO);

        /**
         * 线框模式
         * @param 0: 应用到所有三角形的正反面
         * @param 1: 用线来绘制
        */
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // 设置会默认模式
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        /**
        * 绘制
        * @param 0: 告诉OpenGL需要绘制的图元类型
        * @param 1: 顶点数组的起始索引
        * @param 2: 绘制多少个顶点
        */
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    // 渲染循环结束后释放删除分配的所有资源。
    glfwTerminate();
    
    return 0;
}

unsigned int generateTexture(const std::string imageName) 
{
    int width, height, channels;
    unsigned char *data = stbi_load(imageName.c_str(), &width, &height, &channels, 0);
    if (data == NULL)
    {
        std::cout << "[Texture] Failed to load texture image: " << imageName << std::endl;
        return 0;
    } 
    else
    {
        std::cout << "[Texture] Image name: " << imageName << ", width: " << width << ", height: " << height << ", channel: " << channels << std::endl;
    }
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /**
     * 使用图片数据生成纹理
     * @param 0: 纹理目标，和上边对应为2D
     * @param 1: 多级渐远纹理的级别
     * @param 2: 将纹理存储为哪种格式（图片纹理只有RGB格式）
     * @param 3: 生成纹理的宽度
     * @param 4: 生成纹理的高度
     * @param 5: 无意义，永远为0
     * @param 6: 原图的格式
     * @param 7: 原图的数据类型（使用GRB值加载图片，并存储为char *字节流）
     * @param 8: 图片的元数据
    */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
    // 生成完纹理后释放图片内存
    stbi_image_free(data);

    return texture;
}

GLFWwindow *initWindow()
{
    // 初始化GLFW
    glfwInit();
    // 设置GLFW主次版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MAC OSX needs

    // 创建窗口对象
    GLFWwindow *window = glfwCreateWindow(800, 600, "JayceHan", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    // 将窗口设置为当前线程的上下文
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化GLAD（需要在调用OpenGL接口之前初始化）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }   
    return window;
}