#pragma once
#include "Painter.h"
class HelloLight : public Painter
{

public:
	void OnInit() override;

	void OnRender() override;

	void OnWindowAttach(GLFWwindow* wnd) override;

	void HandleInput(GLFWwindow* wnd) override;

	void  OnMouseMoveCallback(GLFWwindow* window, double xpos, double ypos) override;

	void  OnMouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) override;

	void OnDeInit() override;

private:


};

