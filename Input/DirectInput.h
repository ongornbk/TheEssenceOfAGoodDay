#pragma once
#include "..\Core\Src\corestd.h"

#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"Xinput.lib")
#pragma comment(lib,"dxguid.lib")

class DirectInput
{
public:
	DirectInput(void);
	~DirectInput(void);

	enum DeviceReadingState
	{
		READ_KEYBOARD, READ_MOUSE, READ_KEYBOARDANDMOUSE, READ_NOTHING
	};

	bool Initialize(const HINSTANCE hInstance,const HWND hwnd,const int32 screenWidth,const int32 screenHeight);
	bool Update();
	void Release();

	bool IsKeyDown(const uint32 key) const noexcept;
	bool IsKeyHit(const uint32 key) const noexcept;
	void GetMousePosition(int32& x, int32& y) const noexcept;
	void SetReadingState(const DeviceReadingState readingState) noexcept;
	BYTE GetMouseState(const int32 index) const noexcept;
	bool GetMousePressed(const int32 index) const noexcept;

private:
	const static int32 s_NumKeys = 256;
	static DeviceReadingState m_readingState;

	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();


	IDirectInput8*       m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	DIMOUSESTATE m_mouseState;

	byte m_keys[s_NumKeys];
	byte m_prevKeys[s_NumKeys];

	byte m_prevMouseState[4];

	int32 m_screenWidth;
	int32 m_screenHeight;
	int32 m_mouseX;
	int32 m_mouseY;
};