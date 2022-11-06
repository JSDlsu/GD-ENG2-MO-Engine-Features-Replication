#include "BNS_Credits_UI.h"

#include "BNS_FileExplorer.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"

BNS_Credits_UI::BNS_Credits_UI(std::string name) : BNS_AUIScreen(name)
{
	toShow = false;
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
	ImGui::Text("Developed By: Emerson Celestial");
	ImGui::Text("SPECIAL THANKS");
	ImGui::Text("Sir Patrick");
	ImGui::Text("ImGui: https://github.com/ocornut/imgui/tree/master");
	

	if (ImGui::Button("Close"))
	{
		toShow = false;
	}


	ImGui::End();
}