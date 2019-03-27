#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
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