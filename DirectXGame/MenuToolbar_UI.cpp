#include "MenuToolbar_UI.h"
#include "UIManager.h"

MenuToolbar_UI::MenuToolbar_UI(std::string name) : AUIScreen(name)
{
	toShow = true;
}

void MenuToolbar_UI::DrawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("About"))
		{
			ImGui::MenuItem("Credits", NULL, &UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}
}
