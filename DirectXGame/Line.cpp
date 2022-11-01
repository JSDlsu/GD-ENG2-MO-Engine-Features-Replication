#include "Line.h"
#include "AppWindow.h"
#include "ConstantBuffer.h"
#include "ContantBufferTypes.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "PrimitiveCreation.h"
#include "CameraHandler.h"
#include "EngineTime.h"
#include "ShaderEngine.h"
#include "VertexShaderManager.h"

Line::Line(std::string name, ObjectTypes type) : AGameObject(name, type)
{
	// Set the object type
	ObjectType = type;

	// create CB
	constant_transform cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant_transform));
	// create CB_texture
	constant_texture cc_texture;
	cc_texture.alpha = 1.0f;

}

Line::~Line()
{

}

void Line::Update(float deltaTime, AppWindow* app_window)
{
	// Texture update
	constant_texture cc_texture;
	cc_texture.alpha = alpha;

	// transform update
	constant_transform cc;
	cc.m_time = ::GetTickCount();

	// objects matrix
	Matrix4x4 temp;
	cc.m_world.setIdentity();
	temp.setRotationX(m_rotation.m_x);
	cc.m_world *= temp;
	temp.setRotationY(m_rotation.m_y);
	cc.m_world *= temp;
	temp.setRotationZ(m_rotation.m_z);
	cc.m_world *= temp;
	temp.setScale(m_scale);
	cc.m_world *= temp;
	temp.setTranslation(m_position);
	cc.m_world *= temp;

	// creating the camera matrix
	Matrix4x4 cameraMatrix = CameraHandler::GetInstance()->GetSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

#define VIEW 1
#if VIEW == 0
	// setting for the orthographic projection
	cc.m_proj.setOrthoLH
	(
		Window::WIDTH / 300.0f,
		Window::HEIGHT / 300.0f,
		-40.0f,
		40.0f
	);
#elif VIEW == 1
	// setting the perspective projection
	float aspectRatio = (float)(Window::WIDTH) / (float)(Window::HEIGHT);
	cc.m_proj = CameraHandler::GetInstance()->GetSceneCameraProjectionMatrix();
#endif

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void Line::Draw(const BlenderPtr& m_blender)
{
	// for the transform
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	//SET TEXTURE SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawLineList(2, 0);
	//SET THE BLENDING
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setBlender(m_blender);
}




void Line::SetVertex_Index_Buffer(VertexShaderType vs_type, PC_Cube_ColorData color_data)
{
	PrimitiveCreation::Instance()->ChangeVB_IB_Buffer(vs_type, m_vb, m_ib, color_data);
}

void Line::SetVertexShader(VertexShaderType vs_type)
{
	// assign a new vertexShader to this object
	ShaderEngine::get()->getVertexShaderManager()->ChangeVertexShader(m_vs, vs_type);
	this->vs_type = vs_type;
}

void Line::SetPixelShader(PixelShaderType ps_type)
{
	// assign a new pixelShader to this object
	ShaderEngine::get()->getPixelShaderManager()->ChangePixelShader(m_ps, ps_type);
	this->ps_type = ps_type;
}

void Line::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

float Line::GetAlpha()
{
	return alpha;
}


