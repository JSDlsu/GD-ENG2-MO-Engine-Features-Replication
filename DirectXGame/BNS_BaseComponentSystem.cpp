#include "BNS_BaseComponentSystem.h"
#include "BNS_PhysicsSystem.h"
#include "BNS_TransformSystem.h"

BNS_BaseComponentSystem* BNS_BaseComponentSystem::sharedInstance = nullptr;
BNS_BaseComponentSystem* BNS_BaseComponentSystem::GetInstance()
{
	return sharedInstance;
}

void BNS_BaseComponentSystem::Initialize()
{
	sharedInstance = new BNS_BaseComponentSystem();
}

void BNS_BaseComponentSystem::Destroy()
{
	delete sharedInstance;
}

BNS_TransformSystem* BNS_BaseComponentSystem::GetTransformSystem()
{
	return transformSystem;
}

BNS_PhysicsSystem* BNS_BaseComponentSystem::GetPhysicsSystem()
{
	return physicsSystem;
}

BNS_BaseComponentSystem::BNS_BaseComponentSystem()
{
	// initialize physicsSystem
	this->transformSystem = new BNS_TransformSystem();
	this->physicsSystem = new BNS_PhysicsSystem();
}

BNS_BaseComponentSystem::~BNS_BaseComponentSystem()
{
	delete this->transformSystem;
	delete this->physicsSystem;
}
