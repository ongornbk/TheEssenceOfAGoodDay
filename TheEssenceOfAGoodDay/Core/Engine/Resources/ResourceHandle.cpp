#include "ResourceHandle.h"

ResourceHandle::ResourceHandle(IResource* resource)
{
	assert(resource);
	if (resource)
	{
		mresource = resource;
		mresource->increment_users();
	}
}

ResourceHandle::~ResourceHandle()
{
	assert(mresource);
	if (mresource)
	{
		mresource->decrement_users();
	}
}