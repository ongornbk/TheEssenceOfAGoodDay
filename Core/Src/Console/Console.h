#pragma once
#include "..\corestd.h"
#include "..\String.h"

class Console
{

	enum ConsoleStream
	{
		CON = 0,
		COUT = 1,
		CIN = 2
	};

	mutex in;
	mutex out;
	shared_mutex con;

	Handle HandleOut;
	Handle HandleIn;

	COORD pos;

	Console();

	void lock(ConsoleStream);
	void unlock(ConsoleStream);
	void lock_shared(ConsoleStream);
	void unlock_shared(ConsoleStream);

	void Backspace();
	void GoBack();
	void UpdatePosition();

public:


	~Console();

	friend class ConsoleHandle;
};

class ConsoleHandle
{

	bool   closed = false;
	uint32 id{};

public:

	ConsoleHandle();
	~ConsoleHandle();

	void operator << (String str);
	void operator << (const char* str);
	void operator << (char str);
	void operator << (int32 integer);
	void operator >> (String& str);

	void close();
	void pause();
};