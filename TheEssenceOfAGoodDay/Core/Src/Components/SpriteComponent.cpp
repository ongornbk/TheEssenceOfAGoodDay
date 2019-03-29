#include "Actor.h"
#include "..\..\Engine\Engine.h"
#include "..\..\Engine\Resources\ShaderResource.h"

Components::SpriteComponent::SpriteComponent(Actor* par) : IComponent(par)
{

}

Components::SpriteComponent::~SpriteComponent()
{

}



void Components::SpriteComponent::Initialize()
{
	IComponent* transform = (IComponent*)parent->GetComponent(ComponentType::TRANSFORM_COMPONENT_TYPE);
	if (transform)
		world = &(component_cast<TransformComponent>(transform))->world;
	else throw(exception("Exception at Components::SpriteComponent::Initialize -> No TransformComponent!"));

	constexpr float f[2] = {100.f,100.f};
	sprite.SetSize(f);

	Engine* engine = Engine::GetInstance();

	shaderHandle = ResourceManager::GetInstance()->GetShaderByName(String("texture.fx"),ShaderType::TEXTURE_SHADER_TYPE);

	textureHandle = ResourceManager::GetInstance()->GetTextureByName(String("sprite.png"));

	ShaderResource* shar = (ShaderResource*)shaderHandle->mresource;
	TextureResource* text = (TextureResource*)textureHandle->mresource;

	sprite.Initialize(engine->GetDevice(), shar->GetShader(), text->GetTexture(),true);
}

ComponentType Components::SpriteComponent::GetType() const noexcept
{
	return ComponentType::SPRITE_COMPONENT_TYPE;
}

void Components::SpriteComponent::Update()
{
	sprite.Update();
}

void Components::SpriteComponent::Render(ID3D11DeviceContext* deviceContext, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix)
{
	sprite.Render(deviceContext,*world, viewMatrix, projectionMatrix);
}

void Components::SpriteComponent::Release()
{
	safe_delete(shaderHandle);
	safe_delete(textureHandle);
	delete (this);
}