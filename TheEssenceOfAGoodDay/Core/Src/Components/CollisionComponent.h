#pragma once
#include "..\mmemory.h"
#include "IComponent.h"

class CollisionComponent : public IComponent
{
public:

	float radius{};

	__m128* position{};

	//CollisionComponent(Actor* par)
	//{
//
	//}

	~CollisionComponent()
	{

	}

	void ComponentType GetType() const noexcept override
	{

	}

	void Initialize() override;

}