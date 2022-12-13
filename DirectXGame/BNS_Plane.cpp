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

}

BNS_Plane::~BNS_Plane()
{

}

void BNS_Plane::RecomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Vector3D tempScale(m_scale.m_x * 10.0f, m_scale.m_y * 0.1f, m_scale.m_z * 10.0f);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(tempScale);
	newMatrix *= scaleMatrix;
	Matrix4x4 rotMatrix; rotMatrix.setRotationX(m_rotation.m_x);
	newMatrix *= rotMatrix;
	rotMatrix.setRotationY(m_rotation.m_y);
	newMatrix *= rotMatrix;
	rotMatrix.setRotationZ(m_rotation.m_z);
	newMatrix *= rotMatrix;
	Matrix4x4 transMatrix; transMatrix.setTranslation(m_position);
	newMatrix *= transMatrix;
	m_matrix = newMatrix;
	this->overrideMatrix = true;
}

void BNS_Plane::Update(float deltaTime, BNS_AppWindow* app_window)
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
		Vector3D tempScale(m_scale.m_x * 10.0f, m_scale.m_y * 0.1f, m_scale.m_z * 10.0f);
		temp.setScale(tempScale);
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

void BNS_Plane::Draw(const BlenderPtr& m_blender)
{
	BNS_Cube::Draw(m_blender);
}


