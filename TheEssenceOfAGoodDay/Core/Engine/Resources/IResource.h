#pragma once
#include "..\..\Src\mmemory.h"

class IResource
{

public:

	uint32  GetUsers() const noexcept;

	void    increment_users();
	void    decrement_users();

protected:

	virtual void __load() = 0;
	virtual void __unload() = 0;

	uint32  m_users{};
};