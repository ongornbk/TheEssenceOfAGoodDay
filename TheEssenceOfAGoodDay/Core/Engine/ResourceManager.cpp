#include "ResourceManager.h"
#include "Engine.h"

namespace
{
	ResourceManager* m_instance{};
}

ResourceManager::ResourceManager()
{
	m_instance = this;
	m_shaders.SetFoo(compare_resources_by_name);
}

ResourceManager::~ResourceManager()
{
	vector<Pair<String,IResource*>> releaseResources;
	m_shaders.read(releaseResources);
	for (auto && pair : releaseResources)
	{
		safe_delete(pair.second);
	}
}

ResourceHandle* ResourceManager::GetShaderByName(const String name)
{

	Pair<String, IResource*> pair(name);
	struct Node<Pair<String,IResource*>>* node = m_shaders.find(pair, find_resource_by_name);
	if (node)
	{
		IResource* shader = node->data.second;
		if (shader)
			return new ResourceHandle(shader);
	}

	Engine* engine = Engine::GetInstance();

	ShaderResource* shader = new ShaderResource();
#pragma warning(disable : 4996)
	string str = name.get_string();
	wchar_t* wide_string = new wchar_t[str.length() + 1];
	wstring ws = std::wstring(str.begin(), str.end()).c_str();
	wcscpy(wide_string, ws.c_str());
	shader->Load(engine->GetDevice(), engine->GetHWND(),wide_string);
	delete wide_string;

	m_shaders.push(Pair<String, IResource*>(name, shader));

	return new ResourceHandle(shader);
}

ResourceManager * ResourceManager::GetInstance()
{
	assert(m_instance);
	return m_instance;
}