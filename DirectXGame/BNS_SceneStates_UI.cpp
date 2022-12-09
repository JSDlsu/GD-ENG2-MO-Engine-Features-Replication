#include "BNS_SceneStates_UI.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_UIManager.h"
#include "IMGUI/imgui_internal.h"

BNS_SceneStates_UI::BNS_SceneStates_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{
	
}

BNS_SceneStates_UI::~BNS_SceneStates_UI()
{
}

void BNS_SceneStates_UI::DrawUI()
{
	std::string windowLabel = name + "##" + std::to_string(ID);
	if(ImGui::Begin(windowLabel.c_str()))
	{
		ImVec2 button_size = ImGui::CalcItemSize(ImVec2{ 150, 0 }, 0.0f, 0.0f);

		// obtain size of window
		ImVec2 avail = ImGui::GetWindowSize();

		// calculate centre of window for button. I recommend trying to figure out why this works!
		ImVec2 centre_position_for_button{
			// we have two buttons, so twice the size - and we need to account for the spacing in the middle
			(avail.x - button_size.x * 1 - ImGui::GetStyle().ItemSpacing.x) / 2,
			(avail.y - button_size.y) / 2
		};

		ImGui::SetCursorPos(centre_position_for_button);

		if (ImGui::Button("Play"))
			m_state->setMode(BNS_EngineBackend::PLAY);
		ImGui::SameLine();
		if (ImGui::Button("Pause"))
			m_state->setMode(BNS_EngineBackend::PAUSED);
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
			m_state->setMode(BNS_EngineBackend::EDITOR);
	}

	ImGui::End();
}