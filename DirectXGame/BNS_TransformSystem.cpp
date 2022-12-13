#include "BNS_TransformSystem.h"

#include "BNS_EngineTime.h"
#include "BNS_TransformComponent.h"

BNS_TransformSystem::BNS_TransformSystem()
{
}

BNS_TransformSystem::~BNS_TransformSystem()
{
}

void BNS_TransformSystem::UpdateAllComponents()
{
	BNS_ASystem::UpdateAllComponents();
	//std::cout << "Transform Size: " << componentList.size() << std::endl;
	for (int i = 0; i < componentList.size(); ++i)
	{
		componentList[i]->Perform(BNS_EngineTime::getDeltaTime());
	}
}
