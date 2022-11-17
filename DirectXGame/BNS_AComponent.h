#pragma once
#include <memory>
#include <string>

#include "BNS_EnumHandler.h"

class BNS_AGameObject;
typedef std::shared_ptr<BNS_AGameObject> AGameObjectPtr;
class BNS_AComponent
{
public:
	typedef std::string String;

	BNS_AComponent(String name, ComponentType type, AGameObjectPtr owner);
	virtual ~BNS_AComponent();

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

