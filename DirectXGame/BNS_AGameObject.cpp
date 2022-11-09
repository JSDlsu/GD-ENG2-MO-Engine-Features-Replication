#include "BNS_AGameObject.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <math.h>

BNS_AGameObject::BNS_AGameObject(std::string name, BNS_ObjectTypes type) : name(name), ObjectType(type)
{
	m_position = Vector3D::zero();
	m_scale = Vector3D::one();
	m_rotation = Vector3D::zero();
}

BNS_AGameObject::~BNS_AGameObject()
{
}

void BNS_AGameObject::Draw(const BlenderPtr& m_blender)
{

}

void BNS_AGameObject::SetTransform(Vector3D position, Vector3D scale, Vector3D rotation)
{
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;
}

void BNS_AGameObject::SetPosition(float x, float y, float z)
{
	m_position = Vector3D{ x,y,z };
}

void BNS_AGameObject::SetPosition(Vector3D pos)
{
	m_position = pos;
}

Vector3D BNS_AGameObject::GetLocalPosition()
{
	return m_position;
}

void BNS_AGameObject::SetScale(float x, float y, float z)
{
	m_scale = Vector3D{ x,y,z };
}

void BNS_AGameObject::SetScale(Vector3D scale)
{
	m_scale = scale;
}

Vector3D BNS_AGameObject::GetLocalScale()
{
	return m_scale;
}

void BNS_AGameObject::SetRotation(float x, float y, float z)
{
	m_rotation = Vector3D{ x,y,z };
}

void BNS_AGameObject::SetRotation(Vector3D rot)
{
	m_rotation = rot;
}

Vector3D BNS_AGameObject::GetLocalRotation()
{
	return m_rotation;
}

std::string BNS_AGameObject::GetName()
{
	return name;
}

Matrix4x4 BNS_AGameObject::GetMatrix()
{
	return m_matrix;
}

void BNS_AGameObject::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

float BNS_AGameObject::GetAlpha()
{
	return alpha;
}


