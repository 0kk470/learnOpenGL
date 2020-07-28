#pragma once
#include "glheader.h"

const int MAX_LOGMESSAGE_NUM = 20;

class Debug
{
public:
	static void Log(const std::string& msg);

	static void DrawLogWindow();

	static bool IsOpenDebugWnd;

private:

	static std::vector<std::string> vec_log;

};

