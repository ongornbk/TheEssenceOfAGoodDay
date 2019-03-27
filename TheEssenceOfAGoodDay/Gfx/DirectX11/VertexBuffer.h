#pragma once
#include "Shader\Shader.h"
#include "Vertex.h"

class VertexBuffer
{
public:

	VertexBuffer(void);
	~VertexBuffer(void);

	bool Initialize(ID3D11Device* device, Shader* shader,const float size[2],const bool writeable = false);
	bool InitializeAnchorBottom(ID3D11Device* device, Shader* shader,const float size[2],const bool writeable = false);
	bool InitializePart(ID3D11Device* device, Shader* shader,const float size[2],const float coords[6],const bool writeable = false);
	void Render(ID3D11DeviceContext* deviceContext);
	bool ResizeTexture(ID3D11Device * device,const float size,const bool writeable = false);

	SpriteVertexType* GetVertices();
	ID3D11Buffer* GetVertexBuffer();
	int32 GetIndexCount() const noexcept;
	int32 GetVertexCount() const noexcept;
protected:
	ID3D11Buffer* m_vertexBuffer{};
	ID3D11Buffer* m_indexBuffer{};
	int32 m_vertexCount;
	int32 m_indexCount;
	Shader* m_shader{};
private:

	SpriteVertexType* m_vertices{};
};