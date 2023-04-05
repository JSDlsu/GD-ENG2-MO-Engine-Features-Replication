#pragma once
#include "BNS_AGameObject.h"
#include "BNS_AUIScreen.h"
#include "Vector3D.h"

class BNS_MultipleScene_UI : public BNS_AUIScreen
{
public:
	BNS_MultipleScene_UI(std::string name, int ID);
	~BNS_MultipleScene_UI();
	void DrawUI() override;
private:
	bool active;
};



