#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
class BNS_PhysicsComponent;
class BNS_PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map <String, BNS_PhysicsComponent*> ComponentTable;
	typedef  std::vector<BNS_PhysicsComponent*> ComponentList;

	BNS_PhysicsSystem();
	~BNS_PhysicsSystem();

	void RegisterComponent(BNS_PhysicsComponent* component);
	void UnRegisterComponent(BNS_PhysicsComponent* component);
	void UnRegisterComponentByName(String name);
	BNS_PhysicsComponent* FindComponentByName(String name);
	ComponentList GetAllComponents();

	void UpdateAllComponents();
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

private:
	ComponentTable componentTable;
	ComponentList componentList;

	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};

