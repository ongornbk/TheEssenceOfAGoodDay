#pragma once 
#include "..\..\Core\Src\mmemory.h"
#include "dx11.h"
#include "WICTextureLoader.h"

class Texture
{
public:
	Texture(void);
	~Texture(void);

	bool Initialize(ID3D11Device* device,const WCHAR* fileName);

	ID3D11ShaderResourceView* GetTexture();
	string GetName() const noexcept;
	int32 GetWidth() const noexcept;
	int32 GetHeight() const noexcept;
private:
	ID3D11ShaderResourceView* m_texture{};
	string m_name;
	int32 m_width{};
	int32 m_height{};

};