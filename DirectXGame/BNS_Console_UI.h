#pragma once
#include "BNS_AUIScreen.h"
#include "BNS_EnumHandler.h"
#include "BNS_Log.h"

class BNS_Console_UI : public BNS_AUIScreen
{
public:
	BNS_Console_UI(std::string name, int ID);
	~BNS_Console_UI();
	void DrawUI() override;

	void DrawLog(LogType logType, std::string logMessage);

};



