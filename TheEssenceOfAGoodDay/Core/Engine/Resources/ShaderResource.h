#pragma once
#include "IResource.h"
#include "..\..\..\Gfx\DirectX11\Shader\Shader.h"

class ShaderResource : public IResource
{
public:
	ShaderResource(void);
	~ShaderResource(void);

	bool Load(ID3D11Device* device,const HWND hwnd,const WCHAR* shaderFileName);
	bool Load(Shader* shader);

	Shader* GetShader() const noexcept;
	string GetName() const noexcept;
private:
	Shader* m_shader{};

	wstring mname;

	void __load() override;
	void __unload() override;

};