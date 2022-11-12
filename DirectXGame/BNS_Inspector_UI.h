#pragma once
#include "BNS_AUIScreen.h"

class BNS_Inspector_UI : public BNS_AUIScreen
{
public:
	BNS_Inspector_UI(std::string name);
	~BNS_Inspector_UI();
	void DrawUI() override;

private:
	float positionTest[3] = { 0, 0, 0 };
	float rotationTest[3] = { 0, 0, 0 };
	float scaleTest[3] = { 0, 0, 0 };

	bool transformMenu = true;
};

