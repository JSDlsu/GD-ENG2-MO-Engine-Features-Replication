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

	
	if(ImGui::BeginMenu("Filters"))
	{
		if (ImGui::Button("Show Display"))
		{
			BNS_Log::GetInstance()->setShowDisplay(true);
			BNS_Log::GetInstance()->setShowWarning(false);
			BNS_Log::GetInstance()->setShowError(false);
		}
		if (ImGui::Button("Show Warnings"))
		{
			BNS_Log::GetInstance()->setShowDisplay(false);
			BNS_Log::GetInstance()->setShowWarning(true);
			BNS_Log::GetInstance()->setShowError(false);
		}
		if (ImGui::Button("Show Errors"))
		{
			BNS_Log::GetInstance()->setShowDisplay(false);
			BNS_Log::GetInstance()->setShowWarning(false);
			BNS_Log::GetInstance()->setShowError(true);
		}
		if (ImGui::Button("Show All"))
		{
			BNS_Log::GetInstance()->setShowDisplay(true);
			BNS_Log::GetInstance()->setShowWarning(true);
			BNS_Log::GetInstance()->setShowError(true);
		}
		ImGui::EndMenu();
	}
	
	

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
	BNS_Log::GetInstance()->GetLogList().clear();
	//BNS_Log::GetInstance()->Clear();

	ImGui::End();
}

void BNS_Console_UI::DrawLog(LogType logType, std::string logMessage)
{
	ImGui::Text(logMessage.c_str());
}

