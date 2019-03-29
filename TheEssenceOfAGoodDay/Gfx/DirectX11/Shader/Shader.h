#pragma once
#include "..\dx11.h"
#include "..\..\..\Core\Src\String.h"

enum ShaderType
{
	SHADER_TYPE,
	TEXTURE_SHADER_TYPE
};

class Shader
{
private:
	struct MatrixBufferType
	{
		DirectX::XMMATRIX worldMatrix;
		DirectX::XMMATRIX viewMatrix;
		DirectX::XMMATRIX projectionMatrix;
	};
public:
	Shader(ID3D11Device* device, const HWND hwnd, const WCHAR* shaderFileName);
	Shader(Shader &shader);
	virtual ~Shader(void);
	virtual void Begin(ID3D11DeviceContext* deviceContext);
	virtual void End(ID3D11DeviceContext* deviceContext);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, const DirectX::XMFLOAT4X4 worldMatrix, const DirectX::XMFLOAT4X4 viewMatrix, const DirectX::XMFLOAT4X4 projectionMatrix);


	string GetName() const noexcept;
	bool IsInitialized() const noexcept;

protected:
	virtual bool Initialize(ID3D11Device* device, const HWND hwnd, const WCHAR* shaderFileName);
	bool m_initialized;
private:
	bool InitializeShader(ID3D11Device* device, const HWND hwnd, const WCHAR* shaderFileName);
	void OutputShadeErrorMessage(ID3D10Blob* errorMessage, const HWND hwnd, const WCHAR* shaderFileName);

	ID3D11VertexShader* m_vertexShader{};
	ID3D11PixelShader* m_pixelShader{};
	ID3D11InputLayout* m_layout{};
	ID3D11Buffer* m_matrixBuffer{};
	ID3D11Buffer* m_cameraBuffer{};
	ID3D11BlendState* m_alphaBlendState;
	ID3D11DepthStencilState* m_depthStencilState;
	string m_name;

};