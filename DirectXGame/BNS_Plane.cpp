#include "BNS_Plane.h"

#include "BNS_AppWindow.h"
#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_ConstantBuffer.h"
#include "BNS_ContantBufferTypes.h"
#include "BNS_EngineTime.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_Mesh.h"

BNS_Plane::BNS_Plane(std::string name, BNS_ObjectTypes type) : BNS_Cube(name, type)
{
	SetScale(10, 0.1f, 10);
}

BNS_Plane::~BNS_Plane()
{

}

void BNS_Plane::Update(float deltaTime, BNS_AppWindow* app_window)
{
	BNS_Cube::Update(deltaTime, app_window);
}

void BNS_Plane::Draw(const BlenderPtr& m_blender)
{
	BNS_Cube::Draw(m_blender);
}


