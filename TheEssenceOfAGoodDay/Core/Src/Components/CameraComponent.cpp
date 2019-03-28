#include "Actor.h"

void Components::CameraComponent::Initialize()
{

}

ComponentType Components::CameraComponent::GetType() const noexcept
{
	return ComponentType::CAMERA_COMPONENT_TYPE;
}