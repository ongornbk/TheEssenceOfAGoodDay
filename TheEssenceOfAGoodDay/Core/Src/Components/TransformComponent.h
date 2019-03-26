#pragma once
#include "Component.h"

class TransformComponent : public IComponent
{
	__m128 position{};
	__m128 rotation{};
	__m128 scale{};

	TransformComponent(Actor* parent)
	{

	}


public:

template <class T>
friend T* CreateComponent<T>(Actor* parent);

friend class CollisionComponent;

~TransformComponent()
{

}

void Initialize() override
{

}

};