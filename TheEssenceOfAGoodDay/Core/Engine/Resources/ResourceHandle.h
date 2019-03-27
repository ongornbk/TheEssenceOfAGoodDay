#pragma once
#include "IResource.h"

struct ResourceHandle
{
	ResourceHandle(IResource* resource);
	~ResourceHandle();

	IResource* mresource;
};