#pragma once
#include "..\Core\Src\Components\Actor.h"
#include "..\Core\Src\Console\Console.h"

class Testclass : public Actor
{
	Components::TransformComponent* m_position;
	Components::CollisionComponent* m_collision;
	Components::InputComponent*     m_input;
	Components::SpriteComponent*    m_sprite;

public:

	Testclass()
	{
		m_position = CreateComponent<Components::TransformComponent>(this);
		m_collision = CreateComponent<Components::CollisionComponent>(this);
		m_input = CreateComponent<Components::InputComponent>(this);
		m_sprite = CreateComponent<Components::SpriteComponent>(this);

		m_collision->radius = 10.f;

		InitializeComponents();
	}

	~Testclass()
	{
		ReleaseComponents();
	}

	void Render()
	{
		m_sprite->Render(Engine::GetInstance()->GetDeviceContext(), DirectX::XMFLOAT4X4(), DirectX::XMFLOAT4X4());
	}
	void Tick(const float _In_ dt = 0) noexcept
	{
		m_sprite->Update();
	}
	void Release()
	{
		delete(this);
	}
	void BeginOverlap(const Actor* second)
	{

	}

};