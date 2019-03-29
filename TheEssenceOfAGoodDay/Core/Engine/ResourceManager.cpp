#include "ResourceManager.h"
#include "Engine.h"

//#define CONSOLEMANAGER_DEBUG
#ifdef CONSOLEMANAGER_DEBUG
#include "..\Src\Console\Console.h"
#endif // CONSOLEMANAGER_DEBUG


namespace
{
	ResourceManager* m_instance{};
}

ResourceManager::ResourceManager()
{
	m_instance = this;
	m_shaders.SetFoo(compare_resources_by_name);
	m_textures.SetFoo(compare_resources_by_name);
}

ResourceManager::~ResourceManager()
{
	vector<Pair<String,IResource*>> releaseResources;
	m_shaders.read(releaseResources);
	for (auto && pair : releaseResources)
	{
		safe_delete(pair.second);
	}
	releaseResources.clear();
	m_textures.read(releaseResources);
	for (auto && pair : releaseResources)
	{
		safe_delete(pair.second);
	}
	releaseResources.clear();

}

ResourceHandle* ResourceManager::GetShaderByName(const String name,const ShaderType type)
{

#ifdef CONSOLEMANAGER_DEBUG
	ConsoleHandle con;
	con < "ResourceHandle* ResourceManager::GetShaderByName(const String name) ::: CALLED";
	con < endl;
	con < "name = ";
	con < name;
	con << endl;
#endif // DEBUG
	Pair<String, IResource*> pair(name);
	struct Node<Pair<String,IResource*>>* node = m_shaders.find(pair, find_resource_by_name);
	if (node)
	{
		IResource* shader = node->data.second;
		if (shader)
			return new ResourceHandle(shader);
	}

	Engine* engine = Engine::GetInstance();

	ShaderResource* shader = new ShaderResource(type);
#pragma warning(disable : 4996)
	string str = name.get_string();
	wchar_t* wide_string = new wchar_t[str.length() + 1];
	wstring ws = std::wstring(str.begin(), str.end()).c_str();
	wcscpy(wide_string, ws.c_str());
	bool result = shader->Load(engine->GetDevice(), engine->GetHWND(),wide_string);
	delete wide_string;

	if (result)
	{
#ifdef CONSOLEMANAGER_DEBUG
		ConsoleHandle con;
		con < "ResourceManager :: Loaded -> ";
		con < name;
		con << endl;
#endif // DEBUG
		m_shaders.push(Pair<String, IResource*>(name, shader));
	}
	else
	{
#ifdef CONSOLEMANAGER_DEBUG
			ConsoleHandle con;
			con < "ResourceManager :: Failed to load -> ";
			con < name;
			con << endl;
#endif // DEBUG
	}
		



	return new ResourceHandle(shader);
}

ResourceHandle* ResourceManager::GetTextureByName(const String name)
{
#ifdef CONSOLEMANAGER_DEBUG
	ConsoleHandle con;
	con < "ResourceHandle* ResourceManager::GetTextureByName(const String name) ::: CALLED";
	con < endl;
	con < "name = ";
	con < name;
	con << endl;
#endif // DEBUG
	Pair<String, IResource*> pair(name);
	struct Node<Pair<String, IResource*>>* node = m_textures.find(pair, find_resource_by_name);
	if (node)
	{
		IResource* texture = node->data.second;
		if (texture)
			return new ResourceHandle(texture);
	}

	TextureResource* texture = new TextureResource();
#pragma warning(disable : 4996)
	string str = name.get_string();
	wchar_t* wide_string = new wchar_t[str.length() + 1];
	wstring ws = std::wstring(str.begin(), str.end()).c_str();
	wcscpy(wide_string, ws.c_str());
	bool result = texture->Load(wide_string);
	delete wide_string;

	if (result)
	{
#ifdef CONSOLEMANAGER_DEBUG
		ConsoleHandle con;
		con < "ResourceManager :: Loaded -> ";
		con < name;
		con << endl;
#endif // DEBUG
		m_textures.push(Pair<String, IResource*>(name, texture));
	}
	else
	{
#ifdef CONSOLEMANAGER_DEBUG
		ConsoleHandle con;
		con < "ResourceManager :: Failed to load -> ";
		con < name;
		con << endl;
#endif // DEBUG
	}

	

	return new ResourceHandle(texture);
}

ResourceManager * ResourceManager::GetInstance()
{
	assert(m_instance);
	return m_instance;
}