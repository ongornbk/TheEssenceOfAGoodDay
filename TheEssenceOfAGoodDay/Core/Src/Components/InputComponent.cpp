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

bool Components::InputComponent::MouseButtonPressed(const MouseButton button) const noexcept
{
	return input->GetMousePressed(button);
}
