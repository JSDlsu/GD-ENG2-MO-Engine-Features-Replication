#include "BNS_Sphere.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_ConstantBuffer.h"
#include "BNS_ContantBufferTypes.h"
#include "BNS_EngineTime.h"
#include "BNS_GraphicsEngine.h"

BNS_Sphere::BNS_Sphere(std::string name, BNS_ObjectTypes type) : BNS_AGameObject(name, type)
{
	ObjectType = type;
	DirectX::GeometricPrimitive::CreateSphere(GeometricShapeVertices, GeometricShapeIndices);

	DirectX::GeometricPrimitive::VertexCollection newVerts;
	newVerts.reserve(GeometricShapeVertices.size());

	std::vector<BNS_vertex_color> vertices;
	for(auto it : GeometricShapeVertices)
	{
		vertices.push_back({ Vector3D(it.position.x, it.position.y, it.position.z), Vector3D(1,1,1) });
	}

	/*
	// create the index buffer
	m_ib = BNS_GraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer(GeometricShapeIndices,
		(UINT)list_indices.size());

	// create a BNS_vertex_tex buffer
	m_vb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(&list_vertices[0],
		sizeof(VertexMesh), (UINT)list_vertices.size(),
		BNS_InputLayoutType::MESH);
		*/

	// create CB
	BNS_constant_transform cc;
	cc.m_time = 0;
	cc.alpha = 1.0f;
	m_cb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(&cc, sizeof(BNS_constant_transform));
}

BNS_Sphere::~BNS_Sphere()
{
}

void BNS_Sphere::Update(float deltaTime, BNS_AppWindow* app_window)
{
	// transform update
	BNS_constant_transform cc;
	cc.alpha = alpha;
	//cc.m_time = ::GetTickCount();

	// objects matrix
	Matrix4x4 temp;
	// light matrix
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setRotationY(m_light_rot_y);

	m_light_rot_y += 1.57f * BNS_EngineTime::getDeltaTime();


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
	cc.m_view = BNS_CameraHandler::GetInstance()->GetSceneCameraViewMatrix();
	// setting the perspective projection
	cc.m_proj = BNS_CameraHandler::GetInstance()->GetSceneCameraProjMatrix();
	// update camera position
	cc.m_camera_position = BNS_CameraHandler::GetInstance()->GetSceneCamera()->GetMatrix().getTranslation();
	// update point light position
	float dist_from_origin = 1.0f;
	cc.m_light_position = Vector4D(cos(m_light_rot_y) * dist_from_origin, 3.1f, sin(m_light_rot_y) * dist_from_origin, 1.0f);
	cc.m_light_radius = 100.0f;
	cc.m_light_direction = m_light_rot_matrix.getZDirection();


	// update time
	ticks += BNS_EngineTime::getDeltaTime();
	cc.m_time = ticks;

	m_cb->update(BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext(), &cc);

}

void BNS_Sphere::Draw(const BlenderPtr& m_blender)
{
	
}

void BNS_Sphere::SetMesh(const wchar_t* tex_path)
{
}

void BNS_Sphere::SetTexture(const wchar_t* tex_path)
{
}

void BNS_Sphere::SetVertex_Index_Buffer(BNS_VertexShaderType vs_type, BNS_PC_Cube_ColorData color_data)
{
}

void BNS_Sphere::SetVertexShader(BNS_VertexShaderType vs_type)
{
}

void BNS_Sphere::SetPixelShader(BNS_PixelShaderType ps_type)
{
}
