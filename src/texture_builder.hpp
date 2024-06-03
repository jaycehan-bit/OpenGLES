#include <string>
#ifndef TEXTURE_BUILDER_HPP
#define TEXTURE_BUILDER_HPP
#endif

/**
 * @brief 根据图片生成纹理
 * 
 * @param imageName 图片路径
 * @return unsigned int 纹理ID
 */
unsigned int generateTexture(const std::string imageName);