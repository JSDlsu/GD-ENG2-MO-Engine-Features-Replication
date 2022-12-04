#pragma once
#include "BNS_AUIScreen.h"

class BNS_Inspector_UI : public BNS_AUIScreen
{
public:
	BNS_Inspector_UI(std::string name, int ID);
	~BNS_Inspector_UI();
	void DrawUI() override;

private:
	bool transformMenu = true;
};

