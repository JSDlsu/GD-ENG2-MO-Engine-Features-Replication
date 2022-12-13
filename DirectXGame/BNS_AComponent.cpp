#include "BNS_AComponent.h"

BNS_AComponent::BNS_AComponent(String name, ComponentType type, BNS_AGameObject* owner)
{
    this->name = name;
    this->owner = owner;
    this->type = type;
}

BNS_AComponent::~BNS_AComponent()
{
    type = ComponentType::NotSet;
}

void BNS_AComponent::AttachOwner(BNS_AGameObject* owner)
{
	this->owner = owner;
}

void BNS_AComponent::DetachOwner()
{
    this->owner = nullptr;
    delete this;
}

BNS_AGameObject* BNS_AComponent::GetOwner()
{
    return this->owner;
}

ComponentType BNS_AComponent::GetType()
{
    return this->type;
}

BNS_AComponent::String BNS_AComponent::GetName()
{
    return this->name;
}

void BNS_AComponent::Perform(float deltaTime)
{
}
