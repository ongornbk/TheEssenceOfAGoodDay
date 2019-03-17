#pragma once
#include "..\Src\corestd.h"
#include <LUA/include/lua.hpp>
#include <LUA/include/lualib.h>
#include <LUA/include/lauxlib.h>

typedef int32_t(*lua_CFunction) (lua_State *L);


class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	bool    Initialize(string path,string file) noexcept;
	string  GetPath() noexcept;

	void RegisterFunction(string name, lua_CFunction foo) noexcept;

	static LuaManager* GetInstance() noexcept;

private:

	lua_State* m_lua{};
	string     m_path{};

};
