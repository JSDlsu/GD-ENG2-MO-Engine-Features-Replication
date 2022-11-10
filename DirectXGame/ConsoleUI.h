#pragma once
#include "BNS_AUIScreen.h"
class ConsoleUI : public BNS_AUIScreen
{
public:
	ConsoleUI(std::string name);
	~ConsoleUI();
	void DrawUI() override;
};



