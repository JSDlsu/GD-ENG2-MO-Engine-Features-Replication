#include "BNS_Cube.h"
#include "BNS_AppWindow.h"
#include "BNS_Camera.h"
#include "BNS_ConstantBuffer.h"
#include "BNS_ContantBufferTypes.h"
#include "BNS_DeviceContext.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_IndexBuffer.h"
#include "BNS_Mesh.h"
#include "BNS_PrimitiveCreation.h"
#include "BNS_CameraHandler.h"
#include "BNS_EngineTime.h"
#include "BNS_ShaderEngine.h"
#include "BNS_VertexShaderManager.h"

BNS_Cube::BNS_Cube(std::string name, BNS_ObjectTypes type) : BNS_AGameObject(name, type)
{
	// Set the object type
	ObjectType = type;
	
	// create CB
	BNS_constant_transform cc;
	cc.m_time = 0;
	cc.alpha = 1.0f;
	m_cb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(&cc, sizeof(BNS_constant_transform));
}

BNS_Cube::~BNS_Cube()
{
	std::cout << "Bye bye cube!\n";
}

void BNS_Cube::Update(float deltaTime, BNS_AppWindow* app_window)
{
	// transform update
	BNS_constant_transform cc;
	cc.alpha = alpha;
	//cc.m_time = ::GetTickCount();

	// objects matrix
	Matrix4x4 temp;
	// light matrix
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(m_light_rot_y);

	m_light_rot_y += 0.707f * BNS_EngineTime::getDeltaTime();

	cc.m_light_direction = m_light_rot_matrix.getZDirection();

	cc.m_world.setIdentity();

	if (overrideMatrix) {
		cc.m_world = m_matrix;
	}
	else
	{
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
	}

	// creating the camera matrix
	Matrix4x4 cameraMatrix = BNS_CameraHandler::GetInstance()->GetSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;
	cc.m_camera_position = BNS_CameraHandler::GetInstance()->GetSceneCamera()->GetLocalPosition();

	// setting the perspective projection
	cc.m_proj = BNS_CameraHandler::GetInstance()->GetSceneCameraProjMatrix();

	m_cb->update(BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext(), &cc);
}

void BNS_Cube::Draw(const BlenderPtr& m_blender)
{
	// for the transform
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET TEXTURE SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setVertexShader(m_vs);
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setPixelShader(m_ps);

	if(m_tex != nullptr)
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setTexture(m_ps, m_tex);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setIndexBuffer(m_ib);
	// FINALLY DRAW THE TRIANGLE
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->drawIndexedTriangleList(
		m_ib->getSizeIndexList(), 0, 0);
	//SET THE BLENDING
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setBlender(m_blender);
}

void BNS_Cube::SetMesh(const wchar_t* tex_path)
{
	// sets the new Index and Vertex buffer based from the mesh
	m_mesh = BNS_GraphicsEngine::get()->getMeshManager()->createMeshFromFile(tex_path);
	m_ib = m_mesh.get()->getIndexBuffer();
	m_vb = m_mesh.get()->getVertexBuffer();
}

void BNS_Cube::SetTexture(const wchar_t* tex_path)
{
	// assign the texture file to the BNS_Texture pointer by passing the its path in the file
	m_tex = BNS_GraphicsEngine::get()->getTextureManager()->createTextureFromFile(tex_path);
}

void BNS_Cube::SetVertex_Index_Buffer(BNS_VertexShaderType vs_type, BNS_PC_Cube_ColorData color_data)
{
	BNS_PrimitiveCreation::Instance()->ChangeVB_IB_Buffer(vs_type, m_vb, m_ib, color_data);
}

void BNS_Cube::SetVertexShader(BNS_VertexShaderType vs_type)
{
	// assign a new vertexShader to this object
	BNS_ShaderEngine::get()->getVertexShaderManager()->ChangeVertexShader(m_vs, vs_type);
	this->vs_type = vs_type;
}

void BNS_Cube::SetPixelShader(BNS_PixelShaderType ps_type)
{
	// assign a new pixelShader to this object
	BNS_ShaderEngine::get()->getPixelShaderManager()->ChangePixelShader(m_ps, ps_type);
	this->ps_type = ps_type;
}


