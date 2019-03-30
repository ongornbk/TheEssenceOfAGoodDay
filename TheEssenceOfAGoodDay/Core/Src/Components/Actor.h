#pragma once
#include "..\mmemory.h"
#include "..\Array.h"
#include "..\..\..\Gfx\DirectX11\dx11.h"
#include "..\..\..\Input\Input.h"
#include "..\..\..\Gfx\DirectX11\Sprite.h"
#include "..\..\Engine\Resources\ResourceHandle.h"

	enum ComponentType
	{
		TRANSFORM_COMPONENT_TYPE,
		COLLISION_COMPONENT_TYPE,
		INPUT_COMPONENT_TYPE,
		SPRITE_COMPONENT_TYPE,
		CAMERA_COMPONENT_TYPE
	};

	template <class T>
	inline T* component_cast(Handle component)
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
	virtual void        BeginPlay() = 0;

	Handle GetComponent(const ComponentType type);

protected:

	Array<Handle> m_components;

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
		virtual void          Release() = 0;

	protected:

		IComponent(Actor* par) : parent(par) {}

		Actor*        parent;
	};

	class TransformComponent : public IComponent
	{
	public:

		DirectX::XMFLOAT4 position{};
		DirectX::XMFLOAT4 rotation{};
		DirectX::XMFLOAT4 scale{};

		DirectX::XMFLOAT4X4 world;

		TransformComponent(Actor* par) : IComponent(par) {}
		~TransformComponent() {}

		void Initialize() override;

		ComponentType GetType() const noexcept override;

		void Release() override;

		void Update();

	};

	class CollisionComponent : public IComponent
	{
	public:

		float radius{};

		DirectX::XMFLOAT4* position{};

		CollisionComponent(Actor* par) : IComponent(par) {}

		~CollisionComponent() {}

		void Initialize() override;

		ComponentType GetType() const noexcept override;

		void Release() override;

	};

	class InputComponent : public IComponent
	{
	public:

		InputComponent(Actor* par) : IComponent(par) {}

		~InputComponent() {}

		void Initialize() override;

		ComponentType GetType() const noexcept override;

		bool MouseButtonPressed(const MouseButton button) const;

		bool KeyboardKeyHit(const KeyboardKey key) const;

		void Release() override;

	protected:

		Input* input;

	};

	class SpriteComponent : public IComponent
	{
	public:

		DirectX::XMFLOAT4X4* world;

		SpriteComponent(Actor* par);

		~SpriteComponent();

		void Initialize() override;

		ComponentType GetType() const noexcept override;

		void Release() override;

		 void Update();
		 void Render(ID3D11DeviceContext* deviceContext,DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix);

	protected:

		Sprite sprite;
		ResourceHandle* shaderHandle{};
		ResourceHandle* textureHandle{};

	};

	class CameraComponent : public IComponent
	{
	public:

		CameraComponent(Actor* par);

		void Initialize() override;

		ComponentType GetType() const noexcept override;

		void Release() override;

		void InitializeOrthoMatrix(const int32 screenwidth,const int32 screenheight,const float screennear,const float screenfar);
		void InitializeProjectionMatrix(const float fow,const float screenaspect,const float screennear,const float screenfar);

		void Update();

		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
		DirectX::XMFLOAT4X4 ortho;
		DirectX::XMFLOAT4*  transform_pos;
		DirectX::XMFLOAT4*  transform_rot;
		DirectX::XMVECTOR  position;
		DirectX::XMVECTOR  rotation;
	};


}

