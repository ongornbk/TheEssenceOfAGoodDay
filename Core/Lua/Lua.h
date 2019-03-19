#pragma once
#include "LuaPointer.h"
#include <LUA/include/lua.hpp>
#include <LUA/include/lualib.h>
#include <LUA/include/lauxlib.h>

typedef int32_t(*lua_CFunction) (lua_State *L);


class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	bool    Initialize(string path);
	string  GetPath();

	void RegisterFunction(string name, lua_CFunction foo);

	void RegisterConsoleFunctions();

	static LuaManager* GetInstance();

	bool Execute(string file);


private:

	lua_State* m_lua{};
	string     m_path{};

};
