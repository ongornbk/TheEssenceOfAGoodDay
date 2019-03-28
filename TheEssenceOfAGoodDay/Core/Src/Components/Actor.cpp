#include "Actor.h"

Handle Actor::GetComponent(const ComponentType type)
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
	for (auto & component : m_components)
	{
		BEGIN:
		try
		{
			component_cast<Components::IComponent>(component)->Initialize();
		}
		catch (exception exe)
		{
			const int32 retv = MessageBox(false, exe.what(),"Exception!", 2);
			switch (retv)
			{
			case 3:
			{
				return;
			}
			case 4:
			{
				goto BEGIN;
			}
			case 5:
			{
				continue;
			}
			}
		}
	}
}

void Actor::ReleaseComponents()
{
	for (auto && component : m_components)
	{
		safe_delete(component);
	}
}