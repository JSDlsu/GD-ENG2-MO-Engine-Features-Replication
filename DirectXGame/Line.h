#pragma once
#include "Cube.h"
#include "EnumHandler.h"
#include "Prerequisites.h"
#include "StructHandler.h"

class Line : public Cube
{
public:
	Line(std::string name, ObjectTypes type);
	~Line();
public:
	void Update(float deltaTime, AppWindow* app_window) override;
	void Draw(const BlenderPtr& m_blender) override;
};

