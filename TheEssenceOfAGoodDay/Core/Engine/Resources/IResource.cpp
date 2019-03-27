#include "IResource.h"

uint32 IResource::GetUsers() const noexcept
{
	return m_users;
}

void IResource::decrement_users()
{
	m_users--;
	if (!m_users)
		__unload();
}

void IResource::increment_users()
{
	if (!m_users)
		__load();
	m_users++;
}