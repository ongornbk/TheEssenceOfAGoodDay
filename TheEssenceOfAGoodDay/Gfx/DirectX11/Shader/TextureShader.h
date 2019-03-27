#pragma once
#include "Shader.h"

class TextureShader : public Shader
{
public:
	TextureShader(ID3D11Device* device,const HWND hwnd,const WCHAR* shaderFileName);
	virtual ~TextureShader(void);

	void Begin(ID3D11DeviceContext* deviceContext);
	void End(ID3D11DeviceContext* deviceContext);
protected:
	bool Initialize(ID3D11Device* device,const HWND hwnd,const WCHAR* shaderFileName);
	bool InitializeSamplerState(ID3D11Device * device);
private:
	ID3D11SamplerState* m_samplerState;
};