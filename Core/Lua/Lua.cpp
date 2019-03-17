#include "Lua.h"

#if _WIN64 
#pragma comment(lib,"slib/x64/liblua53.a")
#else
#pragma comment(lib,"slib/x86/liblua53.a")
#endif



namespace
{
	LuaManager* m_instance = nullptr;
}

LuaManager::LuaManager()
{
	m_lua = luaL_newstate();
}

LuaManager::~LuaManager()
{
	lua_close(m_lua);
	m_lua = nullptr;
}

bool  LuaManager::Initialize(string path, string file) noexcept
{
	m_path = path;

	luaL_openlibs(m_lua);
	if (!m_lua)return false;
	bool result;
	result = luaL_loadfile(m_lua, file.c_str());
	if (result)
	{
		fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(m_lua, 1));
		return false;
	}
	result = lua_pcall(m_lua, 0, LUA_MULTRET, 0);
	if (result != LUA_OK) {
		fprintf(stderr, "Lua pcall error: %s\n", lua_tostring(m_lua, 1));
		return false;
	}
	return true;

}

string LuaManager::GetPath() noexcept
{
	return m_path;
}

void LuaManager::RegisterFunction(string name, lua_CFunction foo) noexcept
{
	lua_pushcclosure(m_lua, foo,0);
	lua_setglobal(m_lua, name.c_str());
}

LuaManager * LuaManager::GetInstance() noexcept
{
	return m_instance;
}
