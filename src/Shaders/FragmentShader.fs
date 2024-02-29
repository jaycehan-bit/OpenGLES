#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D textureSampler;

void main()
{
    // FragColor = vec4(outColor, 1.0);
    // 采集纹颜色
    // @param 0: 纹理采集器
    // @param 1: 纹理坐标
    FragColor = texture(textureSampler, TexCoord);
}