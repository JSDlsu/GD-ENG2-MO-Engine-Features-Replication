#include "Line.h"
#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "Mesh.h"

Line::Line(std::string name, ObjectTypes type) : Cube(name, type)
{
	SetScale(0.1f, 1.0f, 0.1f);
	SetRotation(0.0f, 90.0f, 0.0f);
}

Line::~Line()
{

}

void Line::Update(float deltaTime, AppWindow* app_window)
{
	Cube::Update(deltaTime, app_window);
}

void Line::Draw(const BlenderPtr& m_blender)
{
	Cube::Draw(m_blender);
}


