#pragma once
#include "BNS_Cube.h"
#include "BNS_Prerequisites.h"

class BNS_AppWindow;

/*
 * Primitive object. Similar to cube object, but the scale
 * is transformed to a plane scale.
 */
class BNS_Plane : public BNS_Cube
{
public:
	BNS_Plane(std::string name, BNS_ObjectTypes type);
	~BNS_Plane();
	
public:
	void Update(float deltaTime, BNS_AppWindow* app_window = nullptr) override;
	void Draw(const BlenderPtr& m_blender) override;
};

