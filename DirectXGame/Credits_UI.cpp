#include "Credits_UI.h"

Credits_UI::Credits_UI(std::string name) : AUIScreen(name)
{
	toShow = false;
}

void Credits_UI::DrawUI()
{
	//DRAW HERE


	ImGui::Begin("Credits");
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