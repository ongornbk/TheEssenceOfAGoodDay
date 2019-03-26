#include "Actor.h"

void* Actor::GetComponent(const ComponentType type)
{
	for (auto component : m_components)
	{
		if (type == component_cast<Components::IComponent>(component)->GetType())
			return component;
	}
	return nullptr;
}

void Actor::InitializeComponents()
{
	for (auto component : m_components)
	{
		component_cast<Components::IComponent>(component)->Initialize();
	}
}