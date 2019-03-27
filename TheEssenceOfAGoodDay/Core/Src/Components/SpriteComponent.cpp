#include "Actor.h"
#include "..\..\Engine\Engine.h"
#include "..\..\Engine\Resources\ShaderResource.h"

Components::SpriteComponent::SpriteComponent(Actor* par) : IComponent(par)
{

}

Components::SpriteComponent::~SpriteComponent()
{
	safe_delete(shaderHandle);
}



void Components::SpriteComponent::Initialize()
{
	constexpr float f[2] = {100.f,100.f};
	sprite.SetSize(f);

	Engine* engine = Engine::GetInstance();

	shaderHandle = ResourceManager::GetInstance()->GetShaderByName(String("texture.fx"));

	ShaderResource* shar = (ShaderResource*)shaderHandle->mresource;

	sprite.Initialize(engine->GetDevice(), shar->GetShader(), nullptr);
}

ComponentType Components::SpriteComponent::GetType() const noexcept
{
	return ComponentType::SPRITE_COMPONENT_TYPE;
}
