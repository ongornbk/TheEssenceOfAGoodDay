#include "..\Core\Src\Console\Console.h"
#include "..\Core\Src\List.h"
#include "..\Core\Src\Array.h"
#include "..\Core\Src\Array2D.h"
#include "..\Core\Src\LinkedList2D.h"
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

	ConsoleHandle con;

	Engine engine;

	WinApiWindow* window = new WinApiWindow();
	
	window->Initialize(800, 600, String("Glw"), false);

	engine.Initialize(window);

	window->SetCallbackFunction(ddd);

	window->Update();

	con.pause();

	return 0;
}