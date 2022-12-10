#include "BNS_EditorAction.h"

BNS_EditorAction::BNS_EditorAction(BNS_AGameObject* gameObject)
{
	//capture object state
	this->objectName = gameObject->GetName();
	this->localPosition = gameObject->GetLocalPosition();
	this->localRotation = gameObject->GetLocalRotation();
	this->localScale = gameObject->GetLocalScale();
	this->localMatrix = gameObject->GetMatrix();
}

BNS_EditorAction::~BNS_EditorAction()
{
}

std::string BNS_EditorAction::GetOwnerName()
{
    return this->objectName;
}

Vector3D BNS_EditorAction::GetStoredPos()
{
    return this->localPosition;
}

Vector3D BNS_EditorAction::GetStoredScale()
{
    return this->localScale;
}

Vector3D BNS_EditorAction::GetRotation()
{
    return this->localRotation;
}

Matrix4x4 BNS_EditorAction::GetStoredMatrix()
{
    return this->localMatrix;
}
