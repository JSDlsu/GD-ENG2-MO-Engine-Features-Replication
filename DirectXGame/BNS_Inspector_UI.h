#pragma once
#include "BNS_AGameObject.h"
#include "BNS_AUIScreen.h"
#include "Vector3D.h"

class BNS_Inspector_UI : public BNS_AUIScreen
{
public:
	BNS_Inspector_UI(std::string name, int ID);
	~BNS_Inspector_UI();
	void DrawUI() override;


	void updateTransformDisplays(BNS_AGameObject* gameObject, float pos[3], float scale[3], float rot[3]);

	float positionDisplay[3] = { 0.0f, 0.0f, 0.0f };
	float rotationDisplay[3] = { 0.0f, 0.0f, 0.0f };
	float scaleDisplay[3] = { 1.0f, 1.0f, 1.0f };
	

private:
	bool transformMenu = true;
	bool active;
};

