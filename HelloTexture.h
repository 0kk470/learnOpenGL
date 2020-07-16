#pragma once
#include "glheader.h"
#include "SOIL.h"

void HelloTexture(GLFWwindow* window);

GLuint LoadTexture(const GLchar* path, GLint wrapMode = GL_REPEAT, GLint MagFilterMode = GL_LINEAR, GLint MinFilterMode = GL_LINEAR_MIPMAP_LINEAR);

void TextureTest();

void TextureExercise1();

void TextureExercise2();

void TextureExercise3();

void TextureExercise4(GLFWwindow* window);

void UpdateMixValue(GLFWwindow* wnd, GLuint shaderProgram);