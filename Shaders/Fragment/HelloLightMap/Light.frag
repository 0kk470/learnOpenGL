#version 330 core
out vec4 color;

uniform vec3 lightColor;

void main()
{
    color = vec4(lightColor, 1.0f); //设置四维向量的所有元素为 1.0f
}