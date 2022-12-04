#include "BNS_Console_UI.h"
#include "BNS_EngineTime.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"


BNS_Console_UI::BNS_Console_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
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
	std::string windowLabel = name + "##" + std::to_string(ID);
	ImGui::Begin(windowLabel.c_str());
	ImGui::Text(" ");
	ImGui::Text("FPS : %f",fps);
	ImGui::Text("\n");

	/*
	if(!BNS_Log::get()->getLogList().empty())
	{
		for(int i = 0; i < BNS_Log::get()->getLogList().size(); i++)
		{
			ImGui::Text(BNS_Log::get()->getLogList().at(i).c_str());
		}
	}
	*/

	BNS_Log::GetInstance()->Draw();

	ImGui::End();
}

void BNS_Console_UI::DrawLog(LogType logType, std::string logMessage)
{
	ImGui::Text(logMessage.c_str());
}

