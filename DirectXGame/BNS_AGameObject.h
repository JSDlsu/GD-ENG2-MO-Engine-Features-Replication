#pragma once
#include <string>

#include "BNS_EnumHandler.h"
#include "Matrix4x4.h"
#include "BNS_Prerequisites.h"
#include "Vector3D.h"

class Matrix4x4;
class BNS_AppWindow;

/*
 * Abstract class for primitive type objects(cube,plane,sphere,etc..)
 */
class BNS_AGameObject
{
public:
	BNS_AGameObject(std::string name ,BNS_ObjectTypes type);
	virtual ~BNS_AGameObject();
public:
	BNS_ObjectTypes ObjectType;
public:
	virtual void Update(float deltaTime, BNS_AppWindow* app_window) = 0;
	virtual void Draw(const BlenderPtr& m_blender);
public:
	void SetTransform(Vector3D position, Vector3D scale, Vector3D rotation);

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D pos);
	Vector3D GetLocalPosition();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetLocalScale();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3D rot);
	Vector3D GetLocalRotation();

	double GetDistance(const Matrix4x4& camera);
	std::string GetName();

	Matrix4x4 GetMatrix();
protected:
	std::string name;
	Vector3D m_position;
	Vector3D m_scale;
	Vector3D m_rotation;
	Matrix4x4 m_matrix;
};

