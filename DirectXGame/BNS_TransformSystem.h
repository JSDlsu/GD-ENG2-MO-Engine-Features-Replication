#pragma once
#include "BNS_ASystem.h"
class BNS_TransformComponent;

class BNS_TransformSystem : public BNS_ASystem<BNS_TransformComponent>
{
public:
	BNS_TransformSystem();
	~BNS_TransformSystem();

	void UpdateAllComponents() override;
private:

};

