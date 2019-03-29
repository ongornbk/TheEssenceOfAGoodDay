#pragma once
#include "..\Core\Src\Components\Actor.h"
#include "..\Core\Src\Console\Console.h"

class Testclass : public Actor
{
	Components::TransformComponent* m_position;
	Components::CollisionComponent* m_collision;
	Components::InputComponent*     m_input;
	Components::SpriteComponent*    m_sprite;
	Components::CameraComponent*    m_camera;

public:

	Testclass()
	{
		m_position = CreateComponent<Components::TransformComponent>(this);
		m_collision = CreateComponent<Components::CollisionComponent>(this);
		m_input = CreateComponent<Components::InputComponent>(this);
		m_sprite = CreateComponent<Components::SpriteComponent>(this);
		m_camera = CreateComponent<Components::CameraComponent>(this);

		m_collision->radius = 10.f;

		InitializeComponents();
	}

	~Testclass()
	{
		ReleaseComponents();
	}

	void Render() override
	{
		m_sprite->Render(Engine::GetInstance()->GetDeviceContext(), m_camera->view, m_camera->ortho);
	}
	void Tick(const float _In_ dt = 0) noexcept override
	{

		if (m_input->KeyboardKeyHit(KeyboardKey::KEYBOARD_KEY_ESCAPE))
		{
			Engine::GetInstance()->Exit();
		}

		m_sprite->Update();
		m_camera->Update();
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
		Engine* engine = Engine::GetInstance();
		m_camera->InitializeOrthoMatrix(engine->GetScreenWidth(),engine->GetScreenHeight(),1.f / 10.f,1000.f);
		m_camera->InitializeProjectionMatrix(DirectX::XM_PI / 4.f,engine->GetAspectRatio(),1.f / 10.f,1000.f);
	}

};