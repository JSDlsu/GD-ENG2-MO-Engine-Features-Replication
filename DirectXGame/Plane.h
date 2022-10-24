#pragma once
#include "Cube.h"
#include "Prerequisites.h"

class AppWindow;

/*
 * Primitive object. Similar to cube object, but the scale
 * is transformed to a plane scale.
 */
class Plane : public Cube
{
public:
	Plane(std::string name, ObjectTypes type);
	~Plane();
public:
	void Update(float deltaTime, AppWindow* app_window) override;
	void Draw(const VertexShaderPtr& m_vs, const PixelShaderPtr& m_ps, const BlenderPtr& m_blender) override;
};

