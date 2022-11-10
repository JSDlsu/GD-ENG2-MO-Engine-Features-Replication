#pragma once
#include "BNS_AUIScreen.h"
class GameObjectUI : public BNS_AUIScreen
{
public:
	GameObjectUI(std::string name);
	~GameObjectUI();
	void DrawUI() override;

};


