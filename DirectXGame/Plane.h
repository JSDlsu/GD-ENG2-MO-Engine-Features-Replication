#pragma once
#include "Cube.h"
#include "BNS_Prerequisites.h"

class BNS_AppWindow;

/*
 * Primitive object. Similar to cube object, but the scale
 * is transformed to a plane scale.
 */
class Plane : public Cube
{
public:
	Plane(std::string name, BNS_ObjectTypes type);
	~Plane();
public:
	void Update(float deltaTime, BNS_AppWindow* app_window) override;
	void Draw(const BlenderPtr& m_blender) override;
};

