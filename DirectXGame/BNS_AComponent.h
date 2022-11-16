#pragma once
#include <string>

#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"

class BNS_AGameObject;
class BNS_AComponent
{
public:
	typedef std::string String;

	BNS_AComponent(String name, ComponentType type, AGameObjectPtr owner);
	~BNS_AComponent();

	void AttachOwner(AGameObjectPtr owner);
	void DetachOwner();
	AGameObjectPtr GetOwner();
	ComponentType GetType();
	String GetName();

	virtual void Perform(float deltaTime); // performs the associated action.

protected:
	AGameObjectPtr owner;
	ComponentType type;
	String name;
};

