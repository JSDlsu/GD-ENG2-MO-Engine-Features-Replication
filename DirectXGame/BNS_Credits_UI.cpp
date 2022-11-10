#include "BNS_Credits_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_FileExplorer.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"

BNS_Credits_UI::BNS_Credits_UI(std::string name) : BNS_AUIScreen(name)
{
	toShow = false;
}

BNS_Credits_UI::~BNS_Credits_UI()
{
}

void BNS_Credits_UI::DrawUI()
{
	//DRAW HERE
	ImGui::Begin("Credits");

	// assign the texture file to the BNS_Texture pointer by passing the its path in the file
	TexturePtr m_tex = BNS_FileExplorer::GetInstance()->GetImageHashTable()["dlsu_logo"];
	ImGui::Image((void*)m_tex.get()->GetShaderResourceView(), ImVec2(256, 256));

	ImGui::Text("About:");
	ImGui::Text("Scene Editor V.2.0");
	ImGui::Text("Developed By: Emerson Paul P. Celestial");
	ImGui::Text("SPECIAL THANKS");
	ImGui::Text("Sir Patrick");
	ImGui::Text("PardCode");
	ImGui::Text("ImGui: https://github.com/ocornut/imgui/tree/master");
	

	bool temp = dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->IsPerspectiveMode();
	if (ImGui::Button("IsPerspective"))
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->SetPerspectiveMode(!temp);
	}
	if (temp)
		ImGui::Text("Perspective Mode");
	else
		ImGui::Text("Orthographic Mode");
	if (ImGui::Button("Close"))
	{
		toShow = false;
	}


	ImGui::End();
}