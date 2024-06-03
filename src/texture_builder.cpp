#include "texture_builder.hpp"
#include <iostream>
#include "glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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