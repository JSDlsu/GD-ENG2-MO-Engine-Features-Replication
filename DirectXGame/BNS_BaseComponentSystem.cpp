#include "BNS_BaseComponentSystem.h"
#include "BNS_PhysicsSystem.h"

BNS_BaseComponentSystem* BNS_BaseComponentSystem::sharedInstance = NULL;
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

BNS_PhysicsSystem* BNS_BaseComponentSystem::GetPhysicsSystem()
{
	return physicsSystem;
}

BNS_BaseComponentSystem::BNS_BaseComponentSystem()
{
	physicsSystem = new BNS_PhysicsSystem();
}

BNS_BaseComponentSystem::~BNS_BaseComponentSystem()
{
	delete physicsSystem;
}
