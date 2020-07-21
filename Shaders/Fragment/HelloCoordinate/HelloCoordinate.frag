#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
    color = mix(texture(ourTexture0, TexCoord), texture(ourTexture1, TexCoord), 0.2);
}