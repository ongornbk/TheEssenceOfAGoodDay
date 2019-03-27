#pragma once
#include "..\Src\BinaryTree.h"
#include "..\Src\String.h"
#include "..\Src\Pair.h"
#include "Resources\IResource.h"


class ResourceManager
{
	BinaryTree<Pair<String,IResource*>> m_shaders;

public:

	ResourceManager();

	~ResourceManager();


private:

	static bool compare_resources_by_name(const Pair<String, IResource*>& A, const Pair<String, IResource*>& B)
	{
		return A.first < B.first;
	}
};