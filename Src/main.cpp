#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\Threading\ThreadPool.h"
#include "..\Gfx\OpenGl\OpenGlWindow.h"
#include "..\Core\Lua\Lua.h"
#include "..\Core\Src\String.h"
#include "..\Core\Src\Console\Console.h"
#include "..\Core\Src\Stack.h"

#include <string>

void a(void* arg)
{
	int32 result = 0;
	Window* window = (Window*)(arg);
	
	result = window->Initialize(640, 480, "The Essence Of A Good Day");
	if (result)
	{
		{
		ConsoleHandle con;
		con < "OpenGl window creation error! code : ";
		con < result;
		con << endl;
		safe_delete(window);
		}
		return;
	}
	else
	{
		ConsoleHandle con;
		con < "OpenGl window created!";
		con << endl;
	}
	window->Update();
	
	safe_delete(window);
	ConsoleHandle con;
	con < "OpenGl window destroyed!";
	con << endl;
	con.pause();
}

void l(void* arg)
{
	LuaManager* lua = (LuaManager*)arg;

	char buffer[MAX_PATH];
	::GetModuleFileName(NULL, buffer, MAX_PATH);
	lua->Initialize(buffer);


	lua->RegisterConsoleFunctions();
	lua->Execute("test.lua");
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LuaManager* lua = new LuaManager();
	
	ConsoleHandle con;
	
	Thread t(a, NULL, new OpenGlWindow());
	Thread luaT(l, NULL,lua);
	
	luaT.join();
	t.join();
	
	safe_delete(lua);
	
	con < "Press Any Key To Exit...";
	con << endl;
	con.pause();



	

	return 0;
}