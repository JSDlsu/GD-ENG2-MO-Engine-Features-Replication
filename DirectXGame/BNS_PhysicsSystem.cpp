#include "BNS_PhysicsSystem.h"
#include "BNS_PhysicsComponent.h"
#include <iostream>
#include "BNS_EngineTime.h"

BNS_PhysicsSystem::BNS_PhysicsSystem()
{
	// Create the physics engine and world
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81f, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
	std::cout << "Successfully created physics world.\n";
}

BNS_PhysicsSystem::~BNS_PhysicsSystem()
{
	delete this->physicsCommon;
}

void BNS_PhysicsSystem::UpdateAllComponents()
{
	BNS_ASystem::UpdateAllComponents();
	// do not update during first frame. Delta time is still 0.
	if (BNS_EngineTime::getDeltaTime() > 0.0f)
	{
		// update physics world
		this->physicsWorld->update(BNS_EngineTime::getDeltaTime());
		for (int i = 0; i < this->componentList.size(); ++i)
		{
			this->componentList[i]->Perform(BNS_EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* BNS_PhysicsSystem::GetPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* BNS_PhysicsSystem::GetPhysicsCommon()
{
	return this->physicsCommon;
}
