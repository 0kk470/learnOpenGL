#pragma once
#include "glheader.h"


class Painter
{
public:

	virtual void OnInit() {}

	virtual void OnRender() {}

	virtual void OnWindowAttach(GLFWwindow* wnd) {}

	virtual void HandleInput(GLFWwindow* wnd) {}

	virtual void OnDeInit() {}
};

