#include "Plane.h"

#include "BNS_AppWindow.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_Mesh.h"

Plane::Plane(std::string name, BNS_ObjectTypes type) : Cube(name, type)
{
	SetScale(5.0f, 0.1f, 5.0f);
}

Plane::~Plane()
{

}

void Plane::Update(float deltaTime, BNS_AppWindow* app_window)
{
	Cube::Update(deltaTime, app_window);
}

void Plane::Draw(const BlenderPtr& m_blender)
{
	Cube::Draw(m_blender);
}


