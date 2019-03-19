#include "DirectX11.h"
#include "..\..\Core\Src\WinApiWindow.h"

class DirectX11Window : WinApiWindow
{
public:

	int32 Initialize(int32 width, int32 height, String title, bool fullscreen = false);
	int32 Update();


};