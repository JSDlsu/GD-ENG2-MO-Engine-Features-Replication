#include "BNS_MenuToolbar_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
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

	//DRAW HERE
	ImGui::Begin("View Mode");
	
	bool temp = dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->IsPerspectiveMode();
	if (ImGui::Button("IsPerspective"))
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->SetPerspectiveMode(!temp);
	}
	if (temp)
		ImGui::Text("Perspective Mode");
	else
		ImGui::Text("Orthographic Mode");

	ImGui::End();
}
