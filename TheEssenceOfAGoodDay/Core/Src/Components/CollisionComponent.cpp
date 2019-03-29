#include "Actor.h"

void Components::CollisionComponent::Initialize()
{
	IComponent* transform = (IComponent*)parent->GetComponent(ComponentType::TRANSFORM_COMPONENT_TYPE);
	if(transform)
	position = &(component_cast<TransformComponent>(transform))->position;
	else throw(exception("Exception at Components::CollisionComponent::Initialize -> No TransformComponent!"));
}

ComponentType Components::CollisionComponent::GetType() const noexcept
{
	return ComponentType::COLLISION_COMPONENT_TYPE;
}

void Components::CollisionComponent::Release()
{
	delete (this);
}