#include "GameObjectUI.h"
#include "BNS_Credits_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_FileExplorer.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"

GameObjectUI::GameObjectUI(std::string name) : BNS_AUIScreen(name)
{
	toShow = false;
}

GameObjectUI::~GameObjectUI()
{
}

void GameObjectUI::DrawUI()
{
	//DRAW HERE
	ImGui::Begin("GameObject");

	

	ImGui::Text("About:");
	ImGui::Text("Scene Editor V.2.0");
	ImGui::Text("Developed By: Emerson Paul P. Celestial");
	ImGui::Text("SPECIAL THANKS");
	ImGui::Text("Sir Patrick");
	ImGui::Text("PardCode");
	ImGui::Text("ImGui: https://github.com/ocornut/imgui/tree/master");


	ImGui::End();
}