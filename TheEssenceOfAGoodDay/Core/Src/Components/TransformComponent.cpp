#include "Actor.h"

void Components::TransformComponent::Initialize()
{
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixIdentity());
}

ComponentType Components::TransformComponent::GetType() const noexcept
{
		return ComponentType::TRANSFORM_COMPONENT_TYPE;
}

void Components::TransformComponent::Release()
{
	delete (this);
}