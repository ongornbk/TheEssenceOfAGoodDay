#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\Threading\ThreadPool.h"
#include "..\Gfx\OpenGl\OpenGlWindow.h"
#include "..\Core\Src\WinApiWindow.h"
#include "..\Gfx\DirectX11\DirectX11Window.h"
#include "..\Core\Lua\Lua.h"
#include "..\Core\Src\String.h"
#include "..\Core\Src\Console\Console.h"
#include "..\Core\Src\Stack.h"
#include "..\Core\Src\Map.h"

#include <string>

void dxThreadf(void* arg)
{
	int32 result = 0;
	Window* window = (Window*)(arg);
	
	result = window->Initialize(640, 480, String("The Essence Of A Good Day"));
	if (result)
	{
		safe_delete(window);
		ConsoleHandle con;
		con.pause();
		return;
	}

	DirectX11 directX;

	window->Update();
	safe_delete(window);
}

bool _cdecl compare(const int32& a,const int32& b)
{
	return a < b;
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

	//LuaManager* lua = new LuaManager();
	
	
	

	//Thread winapiThread(a, NULL, new WinApiWindow());
	//Thread dxThread(dxThreadf, NULL, new DirectX11Window());

	
	
	//Thread luaT(l, NULL,lua);
	
	//luaT.join();
	//dxThread.join();
	//winapiThread.join();
	
	//safe_delete(lua);

	Map<int32> map(compare);

	Vector<int32> vec;


	for (int i = 0; i < 100; i++)
	{
		map.push(i*(100 - i));
	}

	map.read(vec);

	ConsoleHandle con;

	for (auto i : vec)
	{
		con < i;
		con < endl;
	}

	con < "Press Any Key To Exit...";
	con << endl;
	con.pause();

	return 0;
}