#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\Threading\ThreadPool.h"
#include "..\Gfx\OpenGl\OpenGlWindow.h"
#include "..\Core\Lua\Lua.h"
#include "..\Core\Src\String.h"
#include "..\Core\Src\Console\Console.h"

#include <string>

extern "C"
{

	static int32_t _cdecl testlua(lua_State* state) noexcept
	{
		Vector<String*> vec;
		SplitString(vec,String(lua_tostring(state, 1)), '.');



		for (auto str : vec)
		{
			if (str)
			{
			//	ConsoleHandle con;
			//	con << (*str);
			//	con << endl;
				delete str;
				str = nullptr;
			}
		}
		return 0;
	}

}
void a(void* arg)
{
	int32 result = 0;
	Window* window = (Window*)(arg);
	
	result = window->Initialize(640, 480, "The Essence Of A Good Day");
	if (result)
	{
		{
		ConsoleHandle con;
		con << "OpenGl window creation error! code : ";
		con << result;
		con << endl;
		safe_delete(window);
		}
		return;
	}
	else
	{
		ConsoleHandle con;
		con << "OpenGl window created!";
		con << endl;
	}
	window->Update();
	
	safe_delete(window);
	ConsoleHandle con;
	con << "OpenGl window destroyed!";
	con << endl;
	con.pause();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//LuaManager lua;
	//lua.RegisterFunction("Wololo", testlua);


//	lua.Initialize(argv[0], "test.lua");

	Thread t(a, NULL, new OpenGlWindow());

	ConsoleHandle con;

	String input;
while(true)
{
		input.clear();
		con >> input;
		con << endl;
		if (input == "exit")
			break;
	} 

con.close();

	t.join();



	return 0;
}