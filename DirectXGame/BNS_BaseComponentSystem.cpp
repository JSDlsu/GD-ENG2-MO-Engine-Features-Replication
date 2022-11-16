#include "BNS_BaseComponentSystem.h"

BNS_BaseComponentSystem* BNS_BaseComponentSystem::GetInstance()
{
	return sharedInstance;
}

void BNS_BaseComponentSystem::Initialize()
{
}

void BNS_BaseComponentSystem::Destroy()
{
}

BNS_PhysicsSystem* BNS_BaseComponentSystem::GetPhysicsSystem()
{
}

BNS_BaseComponentSystem::BNS_BaseComponentSystem()
{
}

BNS_BaseComponentSystem::~BNS_BaseComponentSystem()
{
}
