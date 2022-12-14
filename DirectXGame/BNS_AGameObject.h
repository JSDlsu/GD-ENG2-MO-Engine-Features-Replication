#pragma once
#include <string>
#include <vector>

#include "BNS_ContantBufferTypes.h"
#include "BNS_EnumHandler.h"
#include "BNS_PhysicsComponent.h"
#include "BNS_Physics_Prerequisites.h"
#include "Matrix4x4.h"
#include "BNS_Prerequisites.h"
#include "Vector3D.h"


class BNS_AComponent;
class Matrix4x4;
class BNS_AppWindow;
class BNS_TransformComponent;
class BNS_EditorAction;

/*
 * Abstract class for primitive type objects(cube,plane,sphere,etc..)
 */
class BNS_AGameObject
{
	typedef std::string String;
	typedef std::vector<BNS_AComponent*> ComponentList;
	typedef std::vector<BNS_AGameObject*> ChildList;
public:
	BNS_AGameObject(std::string name ,BNS_ObjectTypes type);
	virtual ~BNS_AGameObject();
public:
	BNS_ObjectTypes ObjectType;
public:
	virtual void Update(float deltaTime, BNS_AppWindow* app_window = nullptr) = 0;
	virtual void UpdateTransform();
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

	std::string& GetName();
	void SetAlpha(float alpha);
	float GetAlpha();
	float* GetPhysicsLocalMatrix();

	virtual void RecomputeMatrix(float matrix[16]);
	Matrix4x4 GetMatrix();
public:
	void AttachComponent(BNS_AComponent* component);
	void DetachComponent(BNS_AComponent* component);

	BNS_AComponent* FindComponentByName(String name);
	BNS_AComponent* FindComponentOfType(ComponentType type, String name = "");
	ComponentList GetComponentsOfType(ComponentType type);
	ComponentList GetComponentsOfTypeRecursive(ComponentType type);

public:
	bool GetActive();
	void SetActive(bool flag);

public:
	void saveEditState();
	void restoreEditState();

protected:
	ConstantBufferPtr m_cb;
protected:
	std::string name;
	Vector3D m_position;
	Vector3D m_scale;
	Vector3D m_rotation;
	Matrix4x4 m_matrix;
	float alpha = 1.0f;
	bool overrideMatrix = false;
	bool active;
	BNS_constant_transform cc;
	float m_light_rot_y = 0.0f;
	float ticks = 0.0f;
	bool isChild = false;
public:
	void UpdateChildListTransform();
	void ChildTransform(Matrix4x4 parent_trans);
	void AttachParent(BNS_AGameObject* parent);
	void DetachParent();
	void AttachChild(BNS_AGameObject* child);
	void DetachChild(BNS_AGameObject* child);
	BNS_AGameObject* GetParent();
	ChildList GetChildList();
protected:
	ComponentList componentList;
	ChildList childList;
	BNS_AGameObject* parent = nullptr;
private:
	friend class BNS_TransformComponent;

private:
	BNS_EditorAction* lastEditState = nullptr;
};

