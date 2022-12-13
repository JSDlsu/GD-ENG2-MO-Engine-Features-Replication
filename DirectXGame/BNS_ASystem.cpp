#include "BNS_ASystem.h"
#include <iostream>

#include "BNS_TransformComponent.h"
#include "BNS_PhysicsComponent.h"

// for TransformSystem
template class BNS_ASystem<BNS_TransformComponent>;
// for PhysicsSystem
template class BNS_ASystem<BNS_PhysicsComponent>;

template <class TList>
BNS_ASystem<TList>::BNS_ASystem()
{
}

template <class TList>
BNS_ASystem<TList>::~BNS_ASystem()
{
}

template <class TList>
void BNS_ASystem<TList>::RegisterComponent(TList* component)
{
	componentTable[component->GetName()] = component;
	componentList.push_back(component);
}

template <class TList>
void BNS_ASystem<TList>::UnRegisterComponent(TList* component)
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
			std::cout << "Component Erase" << "\n";
			componentList.erase(componentList.begin() + index);
		}
		
	}
	else
	{
		std::cout << "Component " << component->GetName() << " not registered in system. \n";
	}
}

template <class TList>
void BNS_ASystem<TList>::UnRegisterComponentByName(String name)
{
	if (componentTable[name] != nullptr)
	{
		UnRegisterComponent(componentTable[name]);
	}
}

template <class TList>
TList* BNS_ASystem<TList>::FindComponentByName(String name)
{
	if (componentTable[name] == nullptr)
	{
		std::cout << "Component " << name << " not registered in system.\n";
	}

	return componentTable[name];
}

template <class TList>
typename BNS_ASystem<TList>::ComponentList BNS_ASystem<TList>::GetAllComponents()
{
	return componentList;
}

template <class TList>
void BNS_ASystem<TList>::UpdateAllComponents()
{

}