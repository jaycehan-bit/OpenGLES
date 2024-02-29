#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = vec4(outColor, 1.0);

    // 采集纹颜色
    // @param 0: 纹理采集器
    // @param 1: 纹理坐标
    // FragColor = texture(texture1, TexCoord);

    // 纹理混合
    // 0.2表示20%texture的色值
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

}