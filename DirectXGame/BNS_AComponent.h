#pragma once
#include <memory>
#include <string>

#include "BNS_EnumHandler.h"

class BNS_AGameObject;
class BNS_AComponent
{
public:
	typedef std::string String;

	BNS_AComponent(String name, ComponentType type, BNS_AGameObject* owner);
	virtual ~BNS_AComponent();

	virtual void AttachOwner(BNS_AGameObject* owner);
	virtual void DetachOwner();
	BNS_AGameObject* GetOwner();
	ComponentType GetType();
	String GetName();

	virtual void Perform(float deltaTime); // performs the associated action.

protected:
	BNS_AGameObject* owner;
	ComponentType type;
	String name;
};

