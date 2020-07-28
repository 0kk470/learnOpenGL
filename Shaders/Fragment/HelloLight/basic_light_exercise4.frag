///
#version 330 core
out vec4 color;

in vec3 Light_Color;  
  
uniform vec3 objectColor;

void main()
{
    color = vec4(Light_Color * objectColor, 1.0f);
} 