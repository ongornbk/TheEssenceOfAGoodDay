#include "IResource.h"

//#define IRESOURCE_DEBUG
#ifdef IRESOURCE_DEBUG
#include "..\..\Src\Console\Console.h"
#endif // IRESOURCE_DEBUG


uint32 IResource::GetUsers() const noexcept
{
	return m_users;
}

void IResource::decrement_users()
{
	m_users--;
	if (!m_users)
	{
		__unload();
#ifdef IRESOURCE_DEBUG
		ConsoleHandle con;
		switch (__type())
		{
		case ResourceType::SHADER_RESOURCE:
			con < "SHADER_RESOURCE : ";
			break;
		case ResourceType::TEXTURE_RESOURCE:
			con < "TEXTURE_RESOURCE : ";
		}
		con < __name();
		con < " -> Unloaded!";
		con << endl;
#endif // IRESOURCE_DEBUG

	}
#ifdef IRESOURCE_DEBUG
		ConsoleHandle con;
		switch (__type())
		{
		case ResourceType::SHADER_RESOURCE:
			con < "SHADER_RESOURCE : ";
			break;
		case ResourceType::TEXTURE_RESOURCE:
			con < "TEXTURE_RESOURCE : ";
		}
		con < __name();
		con < " -> --Users = ";
		con < m_users;
		con << endl;
#endif // IRESOURCE_DEBUG



}

void IResource::increment_users()
{
	if (!m_users)
	{
		__load();
#ifdef IRESOURCE_DEBUG
		ConsoleHandle con;
		switch (__type())
		{
		case ResourceType::SHADER_RESOURCE:
			con < "SHADER_RESOURCE : ";
			break;
		case ResourceType::TEXTURE_RESOURCE:
			con < "TEXTURE_RESOURCE : ";
		}
		con < __name();
		con < " -> Loaded!";
		con << endl;
#endif // IRESOURCE_DEBUG
	}
	m_users++;
#ifdef IRESOURCE_DEBUG
	ConsoleHandle con;
	switch (__type())
	{
	case ResourceType::SHADER_RESOURCE:
		con < "SHADER_RESOURCE : ";
		break;
	case ResourceType::TEXTURE_RESOURCE:
		con < "TEXTURE_RESOURCE : ";
	}
	con < __name();
	con < " -> ++Users = ";
	con < m_users;
	con << endl;
#endif // IRESOURCE_DEBUG
}