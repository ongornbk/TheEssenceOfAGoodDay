#include "..\Core\Src\Console\Console.h"
#include "..\Core\Src\List.h"
#include "..\Core\Src\Array.h"
#include "..\Core\Engine\Engine.h"
#include "..\Core\Src\Threading\Thread.h"
#include "..\Gfx\OpenGl\OpenGlWindow.h"
#include "..\Gfx\DirectX11\DirectX11Window.h"
#include "testclass.h"



static void _stdcall ddd(void)
{

	Engine::GetInstance()->Update();
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

	Engine engine;


	WinApiWindow* window = new WinApiWindow();

	window->Initialize(800, 600, String("Glw"), false);

	engine.Initialize(window);

	window->SetCallbackFunction(ddd);

	Testclass tsc;


	ConsoleHandle con;

	window->Update();

	return 0;
}