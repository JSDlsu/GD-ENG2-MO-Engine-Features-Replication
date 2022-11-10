#pragma once
#include "BNS_AUIScreen.h"

class BNS_Hierarchy_UI : public BNS_AUIScreen
{
public:
	BNS_Hierarchy_UI(std::string name);
	~BNS_Hierarchy_UI();
	void DrawUI() override;
};

