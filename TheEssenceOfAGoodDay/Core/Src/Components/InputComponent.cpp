#include "Actor.h"
#include "..\..\Engine\Engine.h"

void Components::InputComponent::Initialize()
{
	input = Engine::GetInstance()->GetInput();
}

ComponentType Components::InputComponent::GetType() const noexcept
{
	return ComponentType::INPUT_COMPONENT_TYPE;
}

bool Components::InputComponent::MouseButtonPressed(const MouseButton button) const
{
	return input->GetMousePressed(button);
}

void Components::InputComponent::Release()
{
	delete (this);
}

bool Components::InputComponent::KeyboardKeyHit(const KeyboardKey key) const
{
	return input->IsKeyHit(key);
}