#include "Lua.h"
#include "..\Src\Console\Console.h"

#if _WIN64 
#pragma comment(lib,"slib/x64/liblua53.a")
#else
#pragma comment(lib,"slib/x86/liblua53.a")
#endif

#pragma region

extern "C"
{
	static int32_t _cdecl LuaConsolePrint(lua_State* state) noexcept
	{
		ConsoleHandle con;
		con << lua_tostring(state, 1);
		return 0;
	}

	static int32_t _cdecl LuaConsolePrintln(lua_State* state) noexcept
	{
		ConsoleHandle con;
		con < lua_tostring(state, 1);
		con << endl;
		return 0;
	}

	static int32_t _cdecl LuaConsoleEndline(lua_State* state) noexcept
	{
		ConsoleHandle con;
		con << endl;
		return 0;
	}

	static int32_t _cdecl LuaConsolePause(lua_State* state) noexcept
	{
		ConsoleHandle con;
		con.pause();
		return 0;
	}

	static int32_t _cdecl LuaConsoleSetTitle(lua_State* state) noexcept
	{
		ConsoleHandle con;
		con.SetTitle(String(lua_tostring(state, 1)));
		return 0;
	}

	static int32_t _cdecl LuaConsoleGetInput(lua_State* state) noexcept
	{
		String str;
		ConsoleHandle con;
		con >> str;
		lua_pushstring(state, str.c_str());
		return 1;
	}
}

#pragma endregion

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

bool  LuaManager::Initialize(string path)
{
	m_path = path;

	luaL_openlibs(m_lua);
	if (!m_lua)return false;

	return true;

}

string LuaManager::GetPath()
{
	return m_path;
}

void LuaManager::RegisterFunction(string name, lua_CFunction foo)
{
	lua_pushcclosure(m_lua, foo,0);
	lua_setglobal(m_lua, name.c_str());
}

void LuaManager::RegisterConsoleFunctions()
{
	RegisterFunction("Print", LuaConsolePrint);
	RegisterFunction("Println", LuaConsolePrintln);
	RegisterFunction("Endline", LuaConsoleEndline);
	RegisterFunction("Pause", LuaConsolePause);
	RegisterFunction("GetInput", LuaConsoleGetInput);
	RegisterFunction("SetConsoleTitle", LuaConsoleSetTitle);
}

LuaManager * LuaManager::GetInstance()
{
	return m_instance;
}

bool LuaManager::Execute(string file)
{
	bool result = luaL_loadfile(m_lua, file.c_str());

	if (result)
	{
		ConsoleHandle con;
		con < "Couldn't load file: ";
		con < lua_tostring(m_lua, 1);
		con << endl;
		return false;
	}

	result = lua_pcall(m_lua, 0, LUA_MULTRET, 0);

if (result != LUA_OK)
{
	ConsoleHandle con;
	con < "Lua pcall error: ";
	con < lua_tostring(m_lua, 1);
	con << endl;
	return false;
}
return true;
}
