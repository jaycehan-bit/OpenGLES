#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "glad.h"
#include "glfw3.h"
#include "Shader.hpp"

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
        return -1;
    }
    // 将窗口设置为当前线程的上下文
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化GLAD（需要在调用OpenGL接口之前初始化）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   

    Shader shader("../src/Shaders/VertexShader.vs", "../src/Shaders/FragmentShader.fs");
    shader.userProgram();
    // 设置窗户位置大小
    // 前两个参数控制窗口左下角位置；后两个参数表示渲染窗口的宽高，以像素为单位。
    glViewport(0, 0, 800, 600);

    // 定义顶点坐标
    const float vertices[] = {
        // 坐标              // 颜色
        // 左上角
        -0.5, 0.5, 0.0,     254/255.0, 67/255.0, 101/255.0,
        // 右上角
        0.5, 0.5, 0.0,      252/255.0, 157/255.0, 154/255.0,
        // 右下角  
        0.5, -0.5, 0.0,     249/255.0, 205/255.0, 173/255.0,
        // 左下角
        -0.5, -0.5, 0.0,    1.0,       245/255.0, 247/255.0,
    };

    const unsigned int indices[] = {
        0, 1, 2,    // 第一个三角形顶点坐标
        0, 2, 3,    // 第二个三角形顶点坐标
    };

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        // glUseProgram(shaderProgram);
        shader.userProgram();

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
