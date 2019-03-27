#pragma once
#include "..\mmemory.h"
#include "..\Array.h"
#include "..\Float4.h"
#include "..\..\..\Input\Input.h"

	enum ComponentType
	{
		TRANSFORM_COMPONENT_TYPE,
		COLLISION_COMPONENT_TYPE,
		INPUT_COMPONENT_TYPE,
		CAMERA_COMPONENT
	};

	template <class T>
	inline T* component_cast(void* component)
	{
		return (T*)(component);
	}


class Actor
{
public:

	virtual void        Render() = 0;
	virtual void        Tick(const float _In_ dt = 0) noexcept = 0;
	virtual void        Release() = 0;
	virtual void        BeginOverlap(const Actor* second) = 0;

	void* GetComponent(const ComponentType type);

protected:

	Array<void*> m_components;

	void InitializeComponents();
	void ReleaseComponents();

	template <class T>
	friend  T* CreateComponent(Actor* par);

};

template <class T>
T* CreateComponent(Actor* par)
{
	T* component = new T(par);
	par->m_components.push_back(component);
	return component;
}



namespace Components
{





	class IComponent
	{
	public:

		virtual void          Initialize()             = 0;
		virtual ComponentType GetType() const noexcept = 0;

	protected:

		IComponent(Actor* par) : parent(par) {}

		Actor*        parent;
	};

	class TransformComponent : public IComponent
	{
	public:

		Float4 position{};
		Float4 rotation{};
		Float4 scale{};

		TransformComponent(Actor* par) : IComponent(par) {}
		~TransformComponent() {}

		void Initialize() override;

		ComponentType GetType() const noexcept override;

	};

	class CollisionComponent : public IComponent
	{
	public:

		float radius{};

		Float4* position{};

		CollisionComponent(Actor* par) : IComponent(par) {}

		~CollisionComponent() {}

		void Initialize() override;

		ComponentType GetType() const noexcept override;



	};

	class InputComponent : public IComponent
	{
	public:

		InputComponent(Actor* par) : IComponent(par) {}

		~InputComponent() {}

		void Initialize() override;

		ComponentType GetType() const noexcept override;

	protected:

		Input* input;

	};


}
