#include "VertexBuffer.h"


namespace
{
	static constexpr uint32 t_indices6[6] = { 0u,1u,2u,0u,2u,3u };
}

VertexBuffer::VertexBuffer()
{

}


VertexBuffer::~VertexBuffer()
{
	safe_delete(m_vertices);
	safe_release(m_vertexBuffer);
	safe_release(m_indexBuffer);
}

bool VertexBuffer::Initialize(ID3D11Device * device, Shader * shader,const float size[2],const bool writeable)
{
	m_shader = shader;
	uint32* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32) * 6);

	float halfSizex = size[0] / 2.f;
	float halfSizey = size[1] / 2.f;

	m_vertices[0].position = DirectX::XMFLOAT3(-halfSizex, -halfSizey, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = DirectX::XMFLOAT3(-halfSizex, halfSizey, 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = DirectX::XMFLOAT3(halfSizex, halfSizey, 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = DirectX::XMFLOAT3(halfSizex, -halfSizey, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (writeable) ? D3D11_CPU_ACCESS_WRITE : 0u;
	vertexBufferDesc.MiscFlags = 0u;
	vertexBufferDesc.StructureByteStride = 0u;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0u;
	vertexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = 0u;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0u;
	indexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] indices;



	return true;
}

bool VertexBuffer::InitializeAnchorBottom(ID3D11Device * device, Shader * shader,const float size[2],const bool writeable)
{
	m_shader = shader;
	uint32* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32) * 6);

	float halfSizex = size[0] / 2.0f;

	m_vertices[0].position = DirectX::XMFLOAT3(-halfSizex, 0.0f, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = DirectX::XMFLOAT3(-halfSizex, size[1], 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = DirectX::XMFLOAT3(halfSizex, size[1], 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = DirectX::XMFLOAT3(halfSizex, 0.0f, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (writeable) ? D3D11_CPU_ACCESS_WRITE : 0u;
	vertexBufferDesc.MiscFlags = 0u;
	vertexBufferDesc.StructureByteStride = 0u;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0u;
	vertexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = 0u;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0u;
	indexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] indices;



	return true;
}

bool VertexBuffer::InitializePart(ID3D11Device * device, Shader * shader,const float size[2],const float coords[6],const bool writeable)
{
	m_shader = shader;
	uint32* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32[m_indexCount];
	memcpy(indices, t_indices6, sizeof(uint32) * 6);

	float halfSizex = size[0] / 2.0f;
	float halfSizey = size[1] / 1.0f;

	const float width = coords[0];
	const float height = coords[1];
	const float left = coords[2];
	const float top = coords[3];
	const float right = coords[4];
	const float bottom = coords[5];

	m_vertices[0].position = DirectX::XMFLOAT3(-halfSizex, -halfSizey, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(left / width, bottom / height);

	m_vertices[1].position = DirectX::XMFLOAT3(-halfSizex, halfSizey, 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(left / width, top / height);

	m_vertices[2].position = DirectX::XMFLOAT3(halfSizex, halfSizey, 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(right / width, top / height);

	m_vertices[3].position = DirectX::XMFLOAT3(halfSizex, -halfSizey, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(right / width, bottom / height);



	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (writeable) ? D3D11_CPU_ACCESS_WRITE : 0u;
	vertexBufferDesc.MiscFlags = 0u;
	vertexBufferDesc.StructureByteStride = 0u;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0u;
	vertexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = 0u;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0u;
	indexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] indices;



	return true;
}

void VertexBuffer::Render(ID3D11DeviceContext * deviceContext)
{
	constexpr uint32_t stride = sizeof(SpriteVertexType);
	constexpr uint32_t offset = 0u;

	deviceContext->IASetVertexBuffers(0u, 1u, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(m_indexCount, 0u, 0);
}

bool VertexBuffer::ResizeTexture(ID3D11Device * device,const float size,const bool writeable)
{

	uint32* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new SpriteVertexType[m_vertexCount];
	indices = new uint32[m_indexCount];

	float halfSize = size / 2.0f;

	m_vertices[0].position = DirectX::XMFLOAT3(-halfSize, -halfSize, 0.0f);
	m_vertices[0].uv = DirectX::XMFLOAT2(0.0f, 1.0f);

	m_vertices[1].position = DirectX::XMFLOAT3(-halfSize, halfSize, 0.0f);
	m_vertices[1].uv = DirectX::XMFLOAT2(0.0f, 0.0f);

	m_vertices[2].position = DirectX::XMFLOAT3(halfSize, halfSize, 0.0f);
	m_vertices[2].uv = DirectX::XMFLOAT2(1.0f, 0.0f);

	m_vertices[3].position = DirectX::XMFLOAT3(halfSize, -halfSize, 0.0f);
	m_vertices[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	vertexBufferDesc.Usage = (writeable) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = (writeable) ? D3D11_CPU_ACCESS_WRITE : 0u;
	vertexBufferDesc.MiscFlags = 0u;
	vertexBufferDesc.StructureByteStride = 0u;

	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0u;
	vertexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	vertexBufferDesc;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = 0u;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0u;
	indexData.SysMemSlicePitch = 0u;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] indices;
	indices = 0;



	return true;
}

SpriteVertexType * VertexBuffer::GetVertices()
{
	return m_vertices;
}

ID3D11Buffer * VertexBuffer::GetVertexBuffer()
{
	return m_vertexBuffer;
}

int32 VertexBuffer::GetIndexCount() const noexcept
{
	return m_indexCount;
}

int32 VertexBuffer::GetVertexCount() const noexcept
{
	return m_vertexCount;
}