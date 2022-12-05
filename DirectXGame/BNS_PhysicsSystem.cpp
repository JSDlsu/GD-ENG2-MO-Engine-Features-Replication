#include "BNS_PhysicsSystem.h"
#include "BNS_PhysicsComponent.h"
#include <iostream>
#include "BNS_EngineTime.h"

BNS_PhysicsSystem::BNS_PhysicsSystem()
{
	// Create the physics engine and world
	physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81f, 0);
	physicsWorld = physicsCommon->createPhysicsWorld(settings);
	std::cout << "Successfully created physics world.\n";
}

BNS_PhysicsSystem::~BNS_PhysicsSystem()
{
	delete physicsCommon;
}

void BNS_PhysicsSystem::UpdateAllComponents()
{
	BNS_ASystem::UpdateAllComponents();
	// do not update during first frame. Delta time is still 0.
	if (BNS_EngineTime::getDeltaTime() > 0.0f)
	{
		// update physics world
		physicsWorld->update(BNS_EngineTime::getDeltaTime());
		for (int i = 0; i < componentList.size(); ++i)
		{
			componentList[i]->Perform(BNS_EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* BNS_PhysicsSystem::GetPhysicsWorld()
{
	return physicsWorld;
}

PhysicsCommon* BNS_PhysicsSystem::GetPhysicsCommon()
{
	return physicsCommon;
}
