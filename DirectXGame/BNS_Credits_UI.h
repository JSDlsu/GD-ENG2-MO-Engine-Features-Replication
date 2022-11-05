#pragma once
#include "BNS_AUIScreen.h"

class BNS_Credits_UI : public BNS_AUIScreen
{
public:
	BNS_Credits_UI(std::string name);
	void DrawUI() override;
};
