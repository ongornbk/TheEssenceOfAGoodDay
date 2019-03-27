#include "Sprite.h"


Sprite::Sprite()
{

}


Sprite::~Sprite(void)
{
	safe_delete(m_vertexBuffer);
}

void Sprite::SetSize(const float size[2])
{
	m_size[0] = size[0];
	m_size[1] = size[1];
}

void Sprite::Initialize(ID3D11Device * device, Shader * shader,Texture* texture,const bool isWriteable)
{
	m_shader = shader;
	m_vertexBuffer = new VertexBuffer();
	(void)m_vertexBuffer->Initialize(device, shader, m_size, isWriteable);
	m_texture = texture;
}


void Sprite::Update()
{

}

void Sprite::Render(ID3D11DeviceContext * deviceContext, DirectX::XMFLOAT4X4 worldMatrix, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix)
{
	if (m_texture)
	{
		m_shader->SetShaderParameters(deviceContext, m_texture->GetTexture());
		m_shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
		m_vertexBuffer->Render(deviceContext);
	}
}

void Sprite::Render(ID3D11DeviceContext * deviceContext, DirectX::XMFLOAT4X4 worldMatrix, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix, Shader* shader)
{
	shader->SetShaderParameters(deviceContext, m_texture->GetTexture());
	shader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	m_vertexBuffer->Render(deviceContext);
}

bool Sprite::ResizeTexture(ID3D11Device * device,const float size,const bool writeable)
{
	if (m_size[0] != size)
	{
		m_size[0] = size;
		return m_vertexBuffer->ResizeTexture(device, size, writeable);
	}
	return true;
}