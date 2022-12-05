#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

#include "BNS_ASystem.h"

using namespace reactphysics3d;
class BNS_PhysicsComponent;
class BNS_PhysicsSystem : public BNS_ASystem<BNS_PhysicsComponent>
{
public:
	BNS_PhysicsSystem();
	~BNS_PhysicsSystem();

	void UpdateAllComponents() override;
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

private:
	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};

