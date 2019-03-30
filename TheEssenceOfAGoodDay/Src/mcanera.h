#pragma once
#include "..\Core\Src\Components\Actor.h"
#include "..\Core\Src\Console\Console.h"
#include "..\Core\Engine\Engine.h"

static Components::CameraComponent*    m_camera;

class mcanera : public Actor
{
	Components::TransformComponent* m_position;
	Components::InputComponent*     m_input;

public:

	mcanera()
	{
		m_position = CreateComponent<Components::TransformComponent>(this);
		m_input = CreateComponent<Components::InputComponent>(this);
		m_camera = CreateComponent<Components::CameraComponent>(this);

		m_position->position.z = -1.f;

		InitializeComponents();
	}

	~mcanera()
	{
		ReleaseComponents();
	}

	void Render() override
	{

	}
	void Tick(const float _In_ dt = 0) noexcept override
	{

		if (m_input->KeyboardKeyHit(KeyboardKey::KEYBOARD_KEY_ESCAPE))
		{
			Engine::GetInstance()->Exit();
		}

		if (m_input->KeyboardKeyHit(KeyboardKey::KEYBOARD_KEY_1))
		{
			Engine::GetInstance()->GetGraphics()->EnableZBuffer(false);
		}

		if (m_input->KeyboardKeyHit(KeyboardKey::KEYBOARD_KEY_2))
		{
			Engine::GetInstance()->GetGraphics()->EnableZBuffer(true);
		}

		if (m_input->KeyboardKeyHit(KeyboardKey::KEYBOARD_KEY_3))
		{
			Engine::GetInstance()->GetGraphics()->EnableAlphaBlending(true);
		}

		if (m_input->KeyboardKeyHit(KeyboardKey::KEYBOARD_KEY_4))
		{
			Engine::GetInstance()->GetGraphics()->EnableAlphaBlending(false);
		}

		m_position->Update();
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
		m_camera->InitializeOrthoMatrix(engine->GetScreenWidth(), engine->GetScreenHeight(), 1.f / 10.f, 1000.f);
		m_camera->InitializeProjectionMatrix(DirectX::XM_PI / 4.f, engine->GetAspectRatio(), 1.f / 10.f, 1000.f);
	}



};