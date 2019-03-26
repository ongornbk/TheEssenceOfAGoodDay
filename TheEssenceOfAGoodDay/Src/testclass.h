#pragma once
#include "..\Core\Src\Actor.h"
#include "..\Core\Src\Components\TransformComponent.h"

class Testclass : public Actor
{
	TransformComponent* m_position;

public:

	Testclass()
	{
		m_position = CreateComponent<TransformComponent>(this);
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