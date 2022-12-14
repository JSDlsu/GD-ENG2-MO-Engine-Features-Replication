#pragma once
#include "BNS_AGameObject.h"
#include "BNS_AUIScreen.h"
#include "Vector3D.h"

class BNS_ViewMode_UI : public BNS_AUIScreen
{
public:
	BNS_ViewMode_UI(std::string name, int ID);
	~BNS_ViewMode_UI();
	void DrawUI() override;
private:
	bool active;
};



