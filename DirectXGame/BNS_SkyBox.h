#pragma once
#include "BNS_Cube.h"

class BNS_SkyBox : public BNS_Cube
{
public:
	BNS_SkyBox(std::string name, BNS_ObjectTypes type);
	~BNS_SkyBox();
public:
	void Update(float deltaTime, BNS_AppWindow* app_window = nullptr) override;
	void Draw(const BlenderPtr& m_blender) override;
};

