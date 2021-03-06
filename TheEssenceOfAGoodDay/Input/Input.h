#pragma once
#include "..\Core\Src\mmemory.h"

class Input
{
public:
	enum DeviceReadingState
	{
		READ_KEYBOARD, READ_MOUSE, READ_KEYBOARDANDMOUSE, READ_NOTHING
	};

	virtual bool Initialize(const HINSTANCE hInstance, const HWND hwnd, const int32 screenWidth, const int32 screenHeight) = 0;
	virtual bool Update() = 0;
	virtual void Release() = 0;
	virtual bool IsKeyDown(const uint32 key) const noexcept = 0;
	virtual bool IsKeyHit(const uint32 key) const noexcept = 0;
	virtual void GetMousePosition(int32& x, int32& y) const noexcept = 0;
	virtual void SetReadingState(const DeviceReadingState readingState) noexcept = 0;
	virtual BYTE GetMouseState(const int32 index) const noexcept = 0;
	virtual bool GetMousePressed(const int32 index) const noexcept = 0;
};

enum MouseButton
{
	MOUSE_LEFT_BUTTON = 0,
	MOUSE_RIGHT_BUTTON = 1
};

enum KeyboardKey
{
	KEYBOARD_KEY_ESCAPE = 0x01,
	KEYBOARD_KEY_1 = 0x02,
	KEYBOARD_KEY_2 = 0x03,
	KEYBOARD_KEY_3 = 0x04,
	KEYBOARD_KEY_4 = 0x05
};