#version 330 core
in vec4 vertexPosition;

out vec4 color;

void main()
{
	color = vertexPosition;
}