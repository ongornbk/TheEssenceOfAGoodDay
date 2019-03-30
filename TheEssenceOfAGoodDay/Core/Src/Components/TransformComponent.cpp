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

void Components::TransformComponent::Update()
{
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranslation(position.x,position.y,position.z));
}