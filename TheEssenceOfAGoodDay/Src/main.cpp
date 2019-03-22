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
#include "..\Core\Src\BinaryTree.h"

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



void l(void* arg)
{
	LuaManager* lua = (LuaManager*)arg;

	char buffer[MAX_PATH];
	::GetModuleFileName(NULL, buffer, MAX_PATH);
	lua->Initialize(buffer);


	lua->RegisterConsoleFunctions();
	lua->Execute("test.lua");
}


bool _cdecl cmp(const String& a, const String& b)
{
	return a < b;
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

	vector<String> strs;
	BinaryTree<String> btree(cmp);

	{
		ConsoleHandle con;
		String str;
		while (true)
		{
			str.clear();
			con >> str;
			if (str == "END")
				break;
			else
				btree.push(str);
		}
	}

	btree.read(strs);

	





	ConsoleHandle con;

	for (auto i : strs)
	{
		con < i;
		con < endl;
	}


	con < String("Press Any Key To Exit...");
	con << endl;
	con.pause();

	//auto a = threads[String("dx")];
	//if (a) a->join();

	//con.pause();

	//threads.release();

	return 0;
}