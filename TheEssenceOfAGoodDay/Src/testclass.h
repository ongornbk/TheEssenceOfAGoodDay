#pragma once
#include "..\Core\Src\Components\Actor.h"

class Testclass : public Actor
{
	Components::TransformComponent* m_position;
	Components::CollisionComponent* m_collision;
	Components::InputComponent*     m_input;

public:

	Testclass()
	{
		m_position = CreateComponent<Components::TransformComponent>(this);
		m_collision = CreateComponent<Components::CollisionComponent>(this);
		m_input = CreateComponent<Components::InputComponent>(this);

		m_collision->radius = 10.f;

		InitializeComponents();
	}

	~Testclass()
	{
		safe_delete(m_position);
	}

	void Render()
	{

	}
	void Tick(const float _In_ dt = 0) noexcept
	{

	}
	void Release()
	{
		delete(this);
	}
	void BeginOverlap(const Actor* second)
	{

	}

};