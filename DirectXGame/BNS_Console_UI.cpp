#include "BNS_Console_UI.h"
#include "BNS_EngineTime.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"

BNS_Console_UI::BNS_Console_UI(std::string name) : BNS_AUIScreen(name)
{
	toShow = false;
}

BNS_Console_UI::~BNS_Console_UI()
{
}

void BNS_Console_UI::DrawUI()
{
	float fps = 0;
	fps = CLOCKS_PER_SEC / BNS_EngineTime::getDeltaTime() * 0.001f;

	
	//DRAW HERE
	ImGui::Begin("Console");

	ImGui::Text(" ");
	ImGui::Text("FPS : %f",fps);
	


	ImGui::End();
}