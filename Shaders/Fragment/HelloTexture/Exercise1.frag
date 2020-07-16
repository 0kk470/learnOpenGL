#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
	//color = texture(ourTexture0, TexCoord) * vec4(ourColor, 1.0f);
	vec2 faceTexCoord = vec2(1 - TexCoord.x, TexCoord.y);
	color = mix(texture(ourTexture0, TexCoord) , texture(ourTexture1, faceTexCoord), 0.2f);
}