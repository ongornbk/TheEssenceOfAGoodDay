#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\ThreadPool.h"
#include "..\Gfx\OpenGl\OpenGlWindow.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

void a(void* arg)
{
	Window* window = (Window*)(arg);
	window->Initialize(640, 480, "The Essence Of A Good Day");
	window->Update();
	
	safe_delete(window);

}

int32 main(int32 argc, char *argv[], char *envp[])
{


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