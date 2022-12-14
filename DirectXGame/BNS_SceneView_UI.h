#pragma once
#include "BNS_AUIScreen.h"

class BNS_SceneView_UI : public BNS_AUIScreen
{
public:
	BNS_SceneView_UI(std::string name, int ID, int cameraID);
	~BNS_SceneView_UI();
	void DrawUI() override;
	int cameraID = -1;
};

