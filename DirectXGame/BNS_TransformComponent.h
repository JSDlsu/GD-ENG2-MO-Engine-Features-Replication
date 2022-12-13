#pragma once
#include "BNS_AComponent.h"

class BNS_TransformComponent : public BNS_AComponent
{
public:
	BNS_TransformComponent(String name, BNS_AGameObject* owner);
	~BNS_TransformComponent() override;
	void DetachOwner() override;
	// executes the physics system per frame
	void Perform(float deltaTime) override;
};

