#include "..\Core\Src\Console\Console.h"
#include "..\Core\Src\List.h"
#include "..\Core\Src\Array.h"



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

	Array<int32> vec;

	for (auto i = 0; i < 10; i++)
		vec.push_back(i);


	ConsoleHandle con;

	for(auto i : vec)
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