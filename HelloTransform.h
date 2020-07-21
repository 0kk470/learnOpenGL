#pragma once

#include "Painter.h"

class HelloTransform: public Painter
{
public:

	virtual void OnInit();

	virtual void OnRender();

	virtual void OnDeInit();

	void TestTransform();

	void ApplyTransform();

	void Exercise1();

	void Exercise2();

private:

	GLuint texture0, texture1;
	GLuint VAO, VBO, EBO;

	Shader* m_PtrShader;
};

