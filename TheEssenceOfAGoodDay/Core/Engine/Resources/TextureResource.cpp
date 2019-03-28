#include "TextureResource.h"
#include "..\Engine.h"

TextureResource::TextureResource()
{

}


TextureResource::~TextureResource()
{
	safe_delete(m_texture);
}

bool TextureResource::Load(const WCHAR* textureFileName)
{
	mname = textureFileName;
	Engine* engine = Engine::GetInstance();
	m_texture = new Texture();
	return m_texture->Initialize(engine->GetDevice(), mname.c_str());
}

Texture* TextureResource::GetTexture() const noexcept
{
	return m_texture;
}

string TextureResource::GetName() const noexcept
{
	assert(m_texture);
	return m_texture->GetName();
}

void TextureResource::__load()
{
	Engine* engine = Engine::GetInstance();
	m_texture = new Texture();
	m_texture->Initialize(engine->GetDevice(), mname.c_str());
}

void TextureResource::__unload()
{
	safe_delete(m_texture);
}