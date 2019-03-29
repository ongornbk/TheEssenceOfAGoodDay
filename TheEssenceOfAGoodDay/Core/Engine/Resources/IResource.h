#pragma once
#include "..\..\Src\mmemory.h"
#include "..\..\Src\String.h"

enum ResourceType
{
	SHADER_RESOURCE,
	TEXTURE_RESOURCE
};

class IResource
{

public:

	uint32  GetUsers() const noexcept;

	void    increment_users();
	void    decrement_users();

protected:

	virtual void __load() = 0;
	virtual void __unload() = 0;

	virtual ResourceType __type() = 0;
	virtual String       __name() = 0;

	uint32  m_users{};
};