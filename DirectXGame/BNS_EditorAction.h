#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "BNS_AGameObject.h"


class BNS_EditorAction
{
public:
	BNS_EditorAction(BNS_AGameObject* gameObject);
	~BNS_EditorAction();

	std::string GetOwnerName();
	Vector3D GetStoredPos();
	Vector3D GetStoredScale();
	Vector3D GetRotation();
	Matrix4x4 GetStoredMatrix();

private:
	std::string objectName;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

