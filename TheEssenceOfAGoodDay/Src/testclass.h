#pragma once
#include "..\Core\Src\Components\Actor.h"
#include "..\Core\Src\Console\Console.h"

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
		ReleaseComponents();
	}

	void Render()
	{

	}
	void Tick(const float _In_ dt = 0) noexcept
	{
		if (m_input->MouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON))
		{
			ConsoleHandle con;
			con < "Panie idz pan juz!";
			con << endl;
		}
		else if(m_input->MouseButtonPressed(MouseButton::MOUSE_RIGHT_BUTTON))
		{
			ConsoleHandle con;
			con < "pMEREERERERERER!";
			con << endl;
		}
	}
	void Release()
	{
		delete(this);
	}
	void BeginOverlap(const Actor* second)
	{

	}

};