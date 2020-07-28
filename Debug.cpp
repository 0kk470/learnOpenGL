#include "Debug.h"

bool Debug::IsOpenDebugWnd = false;

std::vector<std::string> Debug::vec_log;

void Debug::Log(const std::string& msg)
{
	if (vec_log.size() >= MAX_LOGMESSAGE_NUM)
		vec_log.erase(vec_log.begin());
	vec_log.push_back(msg);

	IsOpenDebugWnd = true;
}

void Debug::DrawLogWindow()
{
	if (IsOpenDebugWnd)
	{
		ImGui::SetNextWindowPos(ImVec2(20, 20));
		ImGui::SetNextWindowSize(ImVec2(400, 200));
		ImGui::Begin("Debug Window");
		for (int i = 0; i < vec_log.size(); ++i)
			ImGui::Text(vec_log[i].c_str());
		ImGui::End();
	}
}
