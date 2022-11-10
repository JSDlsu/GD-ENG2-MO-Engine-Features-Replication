#include "BNS_MenuToolbar_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_UIManager.h"

BNS_MenuToolbar_UI::BNS_MenuToolbar_UI(std::string name) : BNS_AUIScreen(name)
{
	toShow = true;
}

BNS_MenuToolbar_UI::~BNS_MenuToolbar_UI()
{
}

void BNS_MenuToolbar_UI::DrawUI()
{
	BNS_UIManager* UM =  BNS_UIManager::GetInstance();
	if (ImGui::BeginMenuBar())
	{
		// About GameEngine
		if (ImGui::BeginMenu("About"))
		{
			ImGui::MenuItem("Credits", NULL, &UM->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		// WindowOptions
		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &UM->opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &UM->opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (UM->dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (UM->dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, UM->opt_fullscreen)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
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
