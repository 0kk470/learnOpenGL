#pragma once
#include "Painter.h"
#include "Resource.h"

class HelloTexture :public Painter
{
public:
	virtual void OnInit();

	virtual void OnRender();

	virtual void HandleInput(GLFWwindow* wnd);

	virtual void OnDeInit();

	void TextureTest();

	void TextureExercise1();

	void TextureExercise2();

	void TextureExercise3();

	void TextureExercise4();

	void UpdateMixValue(GLFWwindow* wnd, GLuint shaderProgram);

private:
	GLuint tex0;
	GLuint tex1;
	GLuint tex_Ex2_0;
	GLuint tex_Ex2_1;
	GLuint tex_Ex3_0;
	GLuint tex_Ex3_1;

	Shader* m_Shader_Default;
	Shader* m_Shader_Ex1;
	Shader* m_Shader_Ex4;

	float m_MixVal;

	GLuint VAO, VBO, EBO;
};