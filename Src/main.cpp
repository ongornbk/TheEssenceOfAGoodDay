#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\ThreadPool.h"
#include "..\Gfx\OpenGl\OpenGlWindow.h"
#include "..\Core\Lua\Lua.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

extern "C"
{

	static int32_t _cdecl testlua(lua_State* state) noexcept
	{
		cout << lua_tostring(state, 1) << endl;
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
		cout << result << endl;
		safe_delete(window);
		return;
	}
	window->Update();
	
	safe_delete(window);

}

int32 main(int32 argc, char *argv[], char *envp[])
{
	LuaManager lua;
	lua.RegisterFunction("Wololo", testlua);


	lua.Initialize(argv[0], "test.lua");

	Thread t(a, NULL, new OpenGlWindow());


	while (true)
	{
		std::string input;
		cin >> input;
		if (input.at(0) == 'q')
			break;
	}

	t.join();

	return 0;
}