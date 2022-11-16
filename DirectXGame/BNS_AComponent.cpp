#include "BNS_AComponent.h"

BNS_AComponent::BNS_AComponent(String name, ComponentType type, AGameObjectPtr owner) : name(name), owner(owner), type(type)
{

}

BNS_AComponent::~BNS_AComponent()
{
    owner = nullptr;
    type = ComponentType::NotSet;
}

void BNS_AComponent::AttachOwner(AGameObjectPtr owner)
{
	owner = owner;
}

void BNS_AComponent::DetachOwner()
{
    //if object owner gets detached. then component must also be deleted.
    owner = nullptr;
    delete this;
}

AGameObjectPtr BNS_AComponent::GetOwner()
{
    return owner;
}

ComponentType BNS_AComponent::GetType()
{
    return type;
}

BNS_AComponent::String BNS_AComponent::GetName()
{
    return name;
}

void BNS_AComponent::Perform(float deltaTime)
{
}
