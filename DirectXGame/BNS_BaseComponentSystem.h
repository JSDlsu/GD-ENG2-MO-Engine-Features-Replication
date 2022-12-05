#pragma once
#include <string>

class BNS_TransformSystem;
class BNS_PhysicsSystem;
class BNS_BaseComponentSystem
{
public:
	typedef std::string String;

	static BNS_BaseComponentSystem* GetInstance();
	static void Initialize();
	static void Destroy();

	BNS_TransformSystem* GetTransformSystem();
	BNS_PhysicsSystem* GetPhysicsSystem();

private:
	BNS_BaseComponentSystem();
	~BNS_BaseComponentSystem();
	BNS_BaseComponentSystem(BNS_BaseComponentSystem const&); // copy constructor is private
	BNS_BaseComponentSystem& operator=(BNS_BaseComponentSystem const&){}; // assignment operator is private
	static  BNS_BaseComponentSystem* sharedInstance;

	BNS_TransformSystem* transformSystem;
	BNS_PhysicsSystem* physicsSystem;
};

