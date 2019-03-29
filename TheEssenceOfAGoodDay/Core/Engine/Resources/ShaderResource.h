#pragma once
#include "IResource.h"
#include "..\..\..\Gfx\DirectX11\Shader\TextureShader.h"

class ShaderResource : public IResource
{
public:
	ShaderResource(const ShaderType type);
	~ShaderResource(void);

	bool Load(ID3D11Device* device,const HWND hwnd,const WCHAR* shaderFileName);

	Shader* GetShader() const noexcept;
	string GetName() const noexcept;
private:
	Shader* m_shader{};

	wstring mname;
	ShaderType mtype;

	void __load() override;
	void __unload() override;
	ResourceType __type() override;
	String       __name() override;


};