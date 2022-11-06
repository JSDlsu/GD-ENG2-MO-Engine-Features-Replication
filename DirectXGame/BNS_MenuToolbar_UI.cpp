#include "BNS_MenuToolbar_UI.h"
#include "BNS_UIManager.h"

BNS_MenuToolbar_UI::BNS_MenuToolbar_UI(std::string name) : BNS_AUIScreen(name)
{
	toShow = true;
}

void BNS_MenuToolbar_UI::DrawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("About"))
		{
			ImGui::MenuItem("Credits", NULL, &BNS_UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow, true);
			ImGui::EndMenu();
		}
		

		ImGui::EndMainMenuBar();
	}
}
