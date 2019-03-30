#include "ShaderResource.h"
#include "..\Engine.h"

ShaderResource::ShaderResource(const ShaderType type)
{
	mtype = type;
}


ShaderResource::~ShaderResource()
{
	safe_delete(m_shader);
}

bool ShaderResource::Load(ID3D11Device * device,const HWND hwnd,const WCHAR* shaderFileName)
{
	mname = shaderFileName;
	switch (mtype)
	{
	case ShaderType::SHADER_TYPE:
		m_shader = new Shader(device, hwnd, shaderFileName);
		break;
	case ShaderType::TEXTURE_SHADER_TYPE:
		m_shader = new TextureShader(device, hwnd, shaderFileName);
		break;
	}
	
	if (!(m_shader)->IsInitialized())
	{
		m_shader = nullptr;
		return false;
	}
	return true;
}

Shader* ShaderResource::GetShader() const noexcept
{
	assert(m_shader);
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
	
	switch (mtype)
	{
	case ShaderType::SHADER_TYPE:
		m_shader = new Shader(engine->GetDevice(), engine->GetHWND(), mname.c_str());
		break;
	case ShaderType::TEXTURE_SHADER_TYPE:
		m_shader = new TextureShader(engine->GetDevice(), engine->GetHWND(), mname.c_str());
		break;
	}
	if (!(m_shader)->IsInitialized())
	{
		safe_delete(m_shader);
	}
}

void ShaderResource::__unload()
{
	safe_delete(m_shader);
}

ResourceType ShaderResource::__type()
{
	return ResourceType::SHADER_RESOURCE;
}

String ShaderResource::__name()
{
	return String(mname);
}