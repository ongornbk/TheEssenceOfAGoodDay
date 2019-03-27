#include "Texture.h"

Texture::Texture()
{

}




Texture::~Texture()
{
	safe_release(m_texture);

	m_name.clear();
}

bool Texture::Initialize(ID3D11Device * device,const WCHAR* fileName)
{
	HRESULT result;
	wstring tmp0 = wstring(fileName);
	string tmp1 = string(tmp0.begin(), tmp0.end());
	m_name = tmp1;

	int32 pos = (int32)m_name.find_last_of("/");
	if (pos >= 0)
	{
		m_name = m_name.substr(pos + 1, m_name.length());
	}
	m_name = m_name.substr(0, m_name.find("."));


	result = DirectX::CreateWICTextureFromFile(device, fileName, NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		return false;
	}

	ID3D11Resource* resource = nullptr;
	m_texture->GetResource(&resource);
	ID3D11Texture2D* texture2D = nullptr;
	result = resource->QueryInterface(&texture2D);
	if (SUCCEEDED(result))
	{
		D3D11_TEXTURE2D_DESC desc;
		texture2D->GetDesc(&desc);
		m_width = desc.Width;
		m_height = desc.Height;
	}

	safe_release(texture2D);
	safe_release(resource);

	return true;
}



ID3D11ShaderResourceView * Texture::GetTexture()
{
	return m_texture;
}

string Texture::GetName() const noexcept
{
	return m_name;
}

int32 Texture::GetWidth() const noexcept
{
	return m_width;
}

int32 Texture::GetHeight() const noexcept
{
	return m_height;
}