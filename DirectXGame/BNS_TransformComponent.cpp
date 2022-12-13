#include "BNS_TransformComponent.h"

#include "BNS_BaseComponentSystem.h"
#include "BNS_CameraHandler.h"
#include "BNS_ConstantBuffer.h"
#include "BNS_ContantBufferTypes.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_TransformSystem.h"
#include "BNS_AGameObject.h"
#include "BNS_Camera.h"
#include "BNS_EngineTime.h"

BNS_TransformComponent::BNS_TransformComponent(String name, BNS_AGameObject* owner) : BNS_AComponent(name, ComponentType::Transform, owner)
{
	BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->RegisterComponent(this);
}

BNS_TransformComponent::~BNS_TransformComponent()
{
	BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UnRegisterComponent(this);
	BNS_AComponent::~BNS_AComponent();
}

void BNS_TransformComponent::DetachOwner()
{
	BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UnRegisterComponent(this);
	BNS_AComponent::DetachOwner();
}

void BNS_TransformComponent::Perform(float deltaTime)
{
	BNS_AComponent::Perform(deltaTime);
	owner->Update(deltaTime);
}
