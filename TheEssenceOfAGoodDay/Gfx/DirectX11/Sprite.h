#pragma once
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader\TextureShader.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite(void);

	virtual void SetSize(const float size[2]);

	virtual void Initialize(ID3D11Device* device, Shader* shader,Texture* texture,const bool isWriteable = false);
	virtual void Update();
	virtual void Render(ID3D11DeviceContext* deviceContext, DirectX::XMFLOAT4X4 worldMatrix, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix);
	virtual void Render(ID3D11DeviceContext * deviceContext, DirectX::XMFLOAT4X4 worldMatrix, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix, Shader* shader);
	virtual bool ResizeTexture(ID3D11Device * device,const float size,const bool writeable = false);
protected:
	VertexBuffer* m_vertexBuffer{};
	Texture* m_texture{};
	Shader* m_shader;
	float m_size[2];

};