#pragma once
#include <string>

#include "BNS_AUIScreen.h"

class BNS_SceneView_UI : public BNS_AUIScreen
{
public:
	BNS_SceneView_UI(std::string name);
	void DrawUI() override;
};

