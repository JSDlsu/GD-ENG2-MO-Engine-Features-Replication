#include "BNS_SkyBox.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_ConstantBuffer.h"
#include "BNS_ContantBufferTypes.h"
#include "BNS_DeviceContext.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_IndexBuffer.h"

BNS_SkyBox::BNS_SkyBox(std::string name, BNS_ObjectTypes type) : BNS_Cube(name, type)
{
	SetScale(100.0f, 100.0f, 100.0f);
}

BNS_SkyBox::~BNS_SkyBox()
{
}

void BNS_SkyBox::Update(float deltaTime, BNS_AppWindow* app_window)
{
	//BNS_Cube::Update(deltaTime, app_window);

	BNS_constant_transform cc;
	
	// update m_matrix
	m_matrix = cc.m_world;

	cc.m_world.setIdentity();

	Matrix4x4 temp;
	temp.setScale(m_scale);
	cc.m_world *= temp;
	temp.setRotationX(m_rotation.m_x);
	cc.m_world *= temp;
	temp.setRotationY(m_rotation.m_y);
	cc.m_world *= temp;
	temp.setRotationZ(m_rotation.m_z);
	cc.m_world *= temp;
	temp.setTranslation(m_position);
	cc.m_world *= temp;
	// update m_matrix
	m_matrix = cc.m_world;
	// creating the camera matrix
	cc.m_view = BNS_CameraHandler::GetInstance()->GetSceneCameraViewMatrix();
	// setting the perspective projection
	cc.m_proj = BNS_CameraHandler::GetInstance()->GetSceneCameraProjMatrix();

	m_cb->update(BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext(), &cc);


}

void BNS_SkyBox::Draw(const BlenderPtr& m_blender)
{
	BNS_Cube::Draw(m_blender);
}
