#version 330 core
out vec4 FragColor;

uniform vec3 borderColor;

void main()
{    
    FragColor = vec4(borderColor,1.0);
}