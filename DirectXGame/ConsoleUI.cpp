#include "ConsoleUI.h"
#include "GameObjectUI.h"
#include "BNS_Credits_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_FileExplorer.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"

ConsoleUI::ConsoleUI(std::string name) : BNS_AUIScreen(name)
{
	toShow = false;
}

ConsoleUI::~ConsoleUI()
{
}

void ConsoleUI::DrawUI()
{
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	current_ticks = clock();

	delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
	if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;
	//DRAW HERE
	ImGui::Begin("Console");

	ImGui::Text(" ");
	ImGui::Text("FPS : %f",fps);
	


	ImGui::End();
}