#pragma once
#include "glheader.h"

#define FRAME_INTETRVAL  (1.0f / Time::Frame)


class Time
{
public:

	static GLfloat deltaTime;

	static GLfloat GameTime;

	static GLuint Frame;
};

