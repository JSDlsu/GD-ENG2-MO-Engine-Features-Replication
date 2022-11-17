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

void BNS_PhysicsSystem::RegisterComponent(BNS_PhysicsComponent* component)
{
	componentTable[component->GetName()] = component;
	componentList.push_back(component);
}

void BNS_PhysicsSystem::UnRegisterComponent(BNS_PhysicsComponent* component)
{
	if (componentTable[component->GetName()] != nullptr)
	{
		componentTable.erase(component->GetName());
		int index = -1;
		for (int i = 0; i < componentList.size(); ++i)
		{
			if (componentList[i] == component)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
		{
			componentList.erase(componentList.begin() + index);
		}
	}
	else
	{
		std::cout << "Component " << component->GetName() << " not registered in physics component. \n";
	}
}

void BNS_PhysicsSystem::UnRegisterComponentByName(String name)
{
	if (componentTable[name] != nullptr)
	{
		UnRegisterComponent(componentTable[name]);
	}
}

BNS_PhysicsComponent* BNS_PhysicsSystem::FindComponentByName(String name)
{
	if (componentTable[name] == nullptr)
	{
		std::cout << "Component " << name << " not registered in physics component.\n";
	}

	return componentTable[name];
}

BNS_PhysicsSystem::ComponentList BNS_PhysicsSystem::GetAllComponents()
{
	return componentList;
}

void BNS_PhysicsSystem::UpdateAllComponents()
{
	// do not update during first frame. Delta time is still 0.
	if (BNS_EngineTime::getDeltaTime() > 0)
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
