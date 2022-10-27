#include "Cube.h"

#include <iostream>

#include "AppWindow.h"
#include "ConstantBuffer.h"
#include "ContantBufferTypes.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "PrimitiveCreation.h"
#include "Camera.h"
#include "CameraHandler.h"
#include "ShaderEngine.h"
#include "VertexShaderManager.h"

Cube::Cube(std::string name, ObjectTypes type) : AGameObject(name, type)
{
	// Set the object type
	ObjectType = type;

	PrimitiveCreation::Instance()->GetCubeWithTexture(m_vb, m_ib);

	// create CB
	constant_transform cc;
	cc.m_time = 0;
	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant_transform));
	// Texture update
	constant_texture cc_texture;
	cc_texture.object_type = (int)ObjectType;
	m_cb_texture = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc_texture, sizeof(constant_texture));

	VertexByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->Get_VS_Default();
	// after a successful compiling, create the vertex_tex buffer then
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(l_vs.m_byte_code, l_vs.m_size);
}

Cube::~Cube()
{

}

void Cube::Update(float deltaTime, AppWindow* app_window)
{
	// Texture update
	constant_texture cc_texture;
	cc_texture.alpha = alpha;
	cc_texture.object_type = (int)ObjectType;
	m_cb_texture->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc_texture);

	// transform update
	constant_transform cc;

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
	float aspectRatio = (float)(Window::WIDTH / 300.0f) / (float)(Window::HEIGHT / 300.0f);
	cc.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 100.0f);
#endif

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void Cube::Draw(const PixelShaderPtr& m_ps, const BlenderPtr& m_blender)
{
	// for the transform
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	// for the texture
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb_texture);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_tex);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(
		m_ib->getSizeIndexList(), 0, 0);
	//SET THE BLENDING
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setBlender(m_blender);
}

void Cube::SetMesh(const wchar_t* tex_path)
{
	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(tex_path);
	m_ib = m_mesh.get()->getIndexBuffer();
	m_vb = m_mesh.get()->getVertexBuffer();
	// Texture update
	constant_texture cc_texture;
	ObjectType = ObjectTypes::MESH;
	cc_texture.object_type = (int)ObjectType;
	m_cb_texture = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc_texture, sizeof(constant_texture));
}

void Cube::SetTexture(const wchar_t* tex_path)
{
	// assign the texture file to the Texture pointer by passing the its path in the file
	m_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(tex_path);
}

void Cube::SetVertexShader(VertexShaderType vs_type)
{
	std::cout << "Set VertexShader\n";
	m_vs = ShaderEngine::get()->getVertexShaderManager()->Get_VS_Default().m_vs;
}

void Cube::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

float Cube::GetAlpha()
{
	return alpha;
}


