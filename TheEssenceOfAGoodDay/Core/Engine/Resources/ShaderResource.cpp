#include "ShaderResource.h"
#include "..\Engine.h"

ShaderResource::ShaderResource()
{

}


ShaderResource::~ShaderResource()
{
	safe_delete(m_shader);
}

bool ShaderResource::Load(ID3D11Device * device,const HWND hwnd,const WCHAR* shaderFileName)
{
	mname = shaderFileName;
	m_shader = new Shader(device, hwnd, shaderFileName);
	if (!(m_shader)->IsInitialized())
	{
		m_shader = nullptr;
		return false;
	}
	return true;
}

bool ShaderResource::Load(Shader * shader)
{
	if (m_shader == nullptr)return false;
	m_shader = shader;
	if (!(m_shader)->IsInitialized())
	{
		m_shader = nullptr;
		return false;
	}
	return true;
}

Shader* ShaderResource::GetShader() const noexcept
{
	return m_shader;
}

string ShaderResource::GetName() const noexcept
{
	assert(m_shader);
	return m_shader->GetName();
}

void ShaderResource::__load()
{
	Engine* engine = Engine::GetInstance();
	m_shader = new Shader(engine->GetDevice(),engine->GetHWND(), mname.c_str());
	if (!(m_shader)->IsInitialized())
	{
		safe_delete(m_shader);
	}
}

void ShaderResource::__unload()
{
	safe_delete(m_shader);
}