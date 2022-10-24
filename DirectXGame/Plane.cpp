#include "Plane.h"

#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "Mesh.h"

Plane::Plane(std::string name, ObjectTypes type) : Cube(name, type)
{
	SetScale(5.0f, 0.1f, 5.0f);
}

Plane::~Plane()
{

}

void Plane::Update(float deltaTime, AppWindow* app_window)
{
	Cube::Update(deltaTime, app_window);
}

void Plane::Draw(const VertexShaderPtr& m_vs, const PixelShaderPtr& m_ps, const BlenderPtr& m_blender)
{
	Cube::Draw(m_vs, m_ps, m_blender);
}


