#pragma once
#include "BNS_AUIScreen.h"
class BNS_Console_UI : public BNS_AUIScreen
{
public:
	BNS_Console_UI(std::string name);
	~BNS_Console_UI();
	void DrawUI() override;
};



