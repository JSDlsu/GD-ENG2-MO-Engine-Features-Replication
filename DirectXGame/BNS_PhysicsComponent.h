#pragma once
#include "BNS_AComponent.h"
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;
class BNS_PhysicsComponent : public BNS_AComponent
{
public:
	BNS_PhysicsComponent(String name, BNS_AGameObject* owner);
	~BNS_PhysicsComponent() override;

	void DetachOwner() override;
	// update rigidBody
	void UpdateRigidBody();
	// executes the physics system per frame
	void Perform(float deltaTime) override;
	RigidBody* GetRigidBody();

private:
	float mass = 1000.0f; // in kilograms
	RigidBody* rigidBody;
	BoxShape* boxShape = nullptr;
};

