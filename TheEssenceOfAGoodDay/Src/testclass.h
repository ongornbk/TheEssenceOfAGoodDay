#pragma once
#include "..\Core\Src\Components\Actor.h"
#include "..\Core\Src\Console\Console.h"
#include "mcanera.h"

class Testclass : public Actor
{
	Components::TransformComponent* m_position;
	Components::CollisionComponent* m_collision;
	Components::SpriteComponent*    m_sprite;

public:

	Testclass()
	{
		m_position = CreateComponent<Components::TransformComponent>(this);
		m_collision = CreateComponent<Components::CollisionComponent>(this);
		m_sprite = CreateComponent<Components::SpriteComponent>(this);

		m_collision->radius = 10.f;

		InitializeComponents();
	}

	~Testclass()
	{
		ReleaseComponents();
	}

	void Render() override
	{
		Components::CameraComponent*    camera = m_camera;
		m_sprite->Render(Engine::GetInstance()->GetDeviceContext(), camera->view, camera->ortho);
	}
	void Tick(const float _In_ dt = 0) noexcept override
	{

		m_position->Update();
		m_sprite->Update();
	}
	void Release() override
	{
		delete(this);
	}
	void BeginOverlap(const Actor* second) override
	{



	}

	void BeginPlay() override
	{

	}

};