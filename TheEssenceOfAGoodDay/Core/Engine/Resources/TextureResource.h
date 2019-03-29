#pragma once
#include "IResource.h"
#include "..\..\..\Gfx\DirectX11\Texture.h"

class TextureResource : public IResource
{
public:
	TextureResource(void);
	~TextureResource(void);

	bool Load(const WCHAR* textureFileName);

	Texture* GetTexture() const noexcept;
	string GetName() const noexcept;
private:
	Texture* m_texture{};

	wstring mname;

	void __load() override;
	void __unload() override;
	ResourceType __type() override;
	String       __name() override;

};