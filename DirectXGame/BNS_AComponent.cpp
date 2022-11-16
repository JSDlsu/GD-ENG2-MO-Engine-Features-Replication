#include "BNS_AComponent.h"

BNS_AComponent::BNS_AComponent(String name, ComponentType type, AGameObjectPtr owner)
{
}

BNS_AComponent::~BNS_AComponent()
{
}

void BNS_AComponent::AttachOwner(AGameObjectPtr owner)
{
	this->owner = owner;
}

void BNS_AComponent::DetachOwner()
{
}

AGameObjectPtr BNS_AComponent::GetOwner()
{
}

ComponentType BNS_AComponent::GetType()
{
}

BNS_AComponent::String BNS_AComponent::GetName()
{
}
