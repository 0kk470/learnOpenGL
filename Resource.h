#pragma once
#include "glheader.h"
#include "stb_image/stb_image.h"


class Resource
{
public:
	static GLuint LoadTexture(const GLchar* path, GLint wrapMode = GL_REPEAT, GLint MagFilterMode = GL_LINEAR, GLint MinFilterMode = GL_LINEAR_MIPMAP_LINEAR);
};

