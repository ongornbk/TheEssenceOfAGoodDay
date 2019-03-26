#include "Actor.h"

void Components::TransformComponent::Initialize()
{

}

ComponentType Components::TransformComponent::GetType() const noexcept
{
		return ComponentType::TRANSFORM_COMPONENT_TYPE;
}