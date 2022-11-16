#include "BNS_AGameObject.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <math.h>

#include "BNS_AComponent.h"

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

void BNS_AGameObject::AttachComponent(BNS_AComponent* component)
{
	componentList.push_back(component);
	AGameObjectPtr temp(this);
	component->AttachOwner(temp);
}

void BNS_AGameObject::DetachComponent(BNS_AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

BNS_AComponent* BNS_AGameObject::FindComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetName() == name) {
			return this->componentList[i];
		}
	}

	return nullptr;
}

BNS_AComponent* BNS_AGameObject::FindComponentOfType(ComponentType type, String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetName() == name && this->componentList[i]->GetType() == type) {
			return this->componentList[i];
		}
	}

	return nullptr;
}

BNS_AGameObject::ComponentList BNS_AGameObject::GetComponentsOfType(ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

BNS_AGameObject::ComponentList BNS_AGameObject::GetComponentsOfTypeRecursive(ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}


void BNS_AGameObject::SetAlpha(float alpha)
{
	this->alpha = alpha;
}

float BNS_AGameObject::GetAlpha()
{
	return alpha;
}

float* BNS_AGameObject::GetPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->GetLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::one()); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->GetLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.MultiplyTo(xMatrix.MultiplyTo(yMatrix.MultiplyTo(zMatrix)));

	allMatrix = allMatrix.MultiplyTo(scaleMatrix.MultiplyTo(rotMatrix));
	allMatrix = allMatrix.MultiplyTo(translationMatrix);

	return allMatrix.GetMatrix();
}


void BNS_AGameObject::SetLocalMatrix(float matrix[16])
{
	m_matrix.setMatrix(matrix);
}


