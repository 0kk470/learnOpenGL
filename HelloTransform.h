#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glheader.h"
#include "HelloTexture.h"

class HelloTransform
{
public:
	static void TransformMain();

	static void TestTransform();

	static void ApplyTransform(GLuint shaderProgram);

	static void Exercise1(GLuint shaderProgram);

	static void Exercise2(GLuint shaderProgram);
};

