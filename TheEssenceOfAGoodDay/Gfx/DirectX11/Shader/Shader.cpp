#include "Shader.h"
#include <d3dcompilerW.h>

#pragma comment(lib,"d3dcompilerW.lib")

namespace
{
	ID3D11SamplerState* m_samplerState;
}

Shader::Shader(ID3D11Device * device,const HWND hwnd,const WCHAR* shaderFileName)
{

	m_initialized = Initialize(device, hwnd, shaderFileName);

	D3D11_SAMPLER_DESC samplerDesc;
	HRESULT result;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1u;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0.f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_samplerState);

	D3D11_BLEND_DESC omDesc;
	ZeroMemory(&omDesc, sizeof(D3D11_BLEND_DESC));
	omDesc.RenderTarget[0].BlendEnable = true;
	omDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	omDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	omDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	omDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	omDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	result = device->CreateBlendState(&omDesc, &m_alphaBlendState);

	D3D11_DEPTH_STENCIL_DESC dsDesc;

	dsDesc.DepthEnable = FALSE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.BackFace = dsDesc.FrontFace;

	result = device->CreateDepthStencilState(&dsDesc, &m_depthStencilState);
}

Shader::Shader(Shader & shader)
{

}


Shader::~Shader(void)
{
	safe_release(m_matrixBuffer);
	safe_release(m_cameraBuffer);
	safe_release(m_layout);
	safe_release(m_pixelShader);
	safe_release(m_vertexShader);
	safe_release(m_alphaBlendState);
	safe_release(m_depthStencilState);

	m_name.clear();
}

bool Shader::Initialize(ID3D11Device* device,const HWND hwnd,const WCHAR* shaderFileName)
{

	wstring shaderFilePath(shaderFileName);
	m_name = string(shaderFilePath.begin(), shaderFilePath.end());
	int32 pos = (int32)m_name.find_last_of("/");
	if (pos >= 0)
	{
		m_name = m_name.substr(pos + 1, m_name.length());
	}



	return InitializeShader(device, hwnd, shaderFileName);
}

void Shader::Begin(ID3D11DeviceContext* deviceContext)
{
	deviceContext->OMSetBlendState(m_alphaBlendState, nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(m_depthStencilState, 0u);
	deviceContext->PSSetSamplers(1u, 1u, &m_samplerState);
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0u);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0u);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Shader::End(ID3D11DeviceContext * deviceContext)
{
	deviceContext->PSSetSamplers(0u, 0u, nullptr);
	deviceContext->IASetInputLayout(nullptr);
	deviceContext->VSSetShader(nullptr, nullptr, 0u);
	deviceContext->PSSetShader(nullptr, nullptr, 0u);
}


bool Shader::SetShaderParameters(ID3D11DeviceContext * deviceContext,ID3D11ShaderResourceView * texture)
{
	deviceContext->PSSetShaderResources(0u, 1u, &texture);
	return true;
}



bool Shader::SetShaderParameters(ID3D11DeviceContext * deviceContext,const DirectX::XMFLOAT4X4 worldMatrix,const DirectX::XMFLOAT4X4 viewMatrix,const DirectX::XMFLOAT4X4 projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;




	result = deviceContext->Map(m_matrixBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->worldMatrix = XMMatrixTranspose(XMLoadFloat4x4(&worldMatrix));
	dataPtr->viewMatrix = XMMatrixTranspose(XMLoadFloat4x4(&viewMatrix));
	dataPtr->projectionMatrix = XMMatrixTranspose(XMLoadFloat4x4(&projectionMatrix));

	deviceContext->Unmap(m_matrixBuffer, 0u);


	deviceContext->VSSetConstantBuffers(0u, 1u, &m_matrixBuffer);


	return true;
}

string Shader::GetName() const noexcept
{
	return m_name;
}

bool Shader::IsInitialized() const noexcept
{
	return m_initialized;
}

bool Shader::InitializeShader(ID3D11Device* device,const HWND hwnd,const WCHAR* shaderFileName)
{
	HRESULT result;
	ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	uint32 numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	result = D3DCompileFromFile(shaderFileName, nullptr, nullptr, "VSMain", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShadeErrorMessage(errorMessage, hwnd, shaderFileName);
		}
		else
		{
			wstring tmp0 = wstring(shaderFileName);
			string tmp1 = string(tmp0.begin(), tmp0.end());
			MessageBox(hwnd, tmp1.c_str(), "Error in Shader File VS", MB_OK);
		}
		return false;
	}
	result = D3DCompileFromFile(shaderFileName, nullptr, nullptr, "PSMain", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0u, &pixelShaderBuffer, &errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShadeErrorMessage(errorMessage, hwnd, shaderFileName);
		}
		else
		{
			wstring tmp0 = wstring(shaderFileName);
			string tmp1 = string(tmp0.begin(), tmp0.end());
			MessageBox(hwnd, tmp1.c_str(), "Error in Shader File PS", MB_OK);
		}
		return false;
	}

	safe_release(errorMessage);

	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0u;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0u;
	polygonLayout[0].AlignedByteOffset = 0u;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0u;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0u;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0u;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0u;



	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	release(vertexShaderBuffer);
	release(pixelShaderBuffer);

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0u;
	matrixBufferDesc.StructureByteStride = 0u;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Shader::OutputShadeErrorMessage(ID3D10Blob * errorMessage,const HWND hwnd,const WCHAR* shaderFileName)
{
	int8* compileErrors = (int8*)errorMessage->GetBufferPointer();
	uint32 bufferSize = (uint32)(errorMessage->GetBufferSize());

	ofstream fout;
	fout.open("shader-error-txt");
	for (uint32 i = 0u; i < bufferSize; ++i)
	{
		fout << compileErrors[i];
	}
	fout.close();

	release(errorMessage);

	return;
}