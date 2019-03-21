#pragma once
#include "..\corestd.h"
#include "..\String.h"
#include "..\Queue.h"
#include "..\Pair.h"

class Console
{

	enum ConsoleStream
	{
		CON = 0,
		COUT = 1,
		CIN = 2,
		DEL = 3
	};

	enum ConsoleStance
	{
		OPEN = 0,
		PRINTING = 1,
		RECEIVING = 2,
		PAUSED = 3,
		CLOSED
	};

	mutex in;
	mutex out;
	mutex del;

	shared_mutex con;

	Handle HandleOut;
	Handle HandleIn;

	atomic<ConsoleStance> cstance;

	IStruct<Pair<String,String>>* delayedOut;

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

	String mformat;
public:

	enum HandleStance
	{
		BLOCKED,
		UNBLOCKED
	};

	ConsoleHandle();
	~ConsoleHandle();

	void operator < (String str);
	void operator < (const char* str);
	void operator < (const unsigned char* str);
	void operator < (char str);
	void operator < (int32 integer);
	void operator < (const int64 integer);
	void operator < (const uint64 integer);
	void operator << (String str);
	void operator << (const char* str);
	void operator << (const unsigned char* str);
	void operator << (char str);
	void operator << (const int32 integer);


	void operator >> (String& str);
	void operator >  (String& str);

	void close();
	void pause();
	void format(const char* form) noexcept;
	void format(const String form) noexcept;
	void format() noexcept;

	void SetTitle(String str);

private:

	HandleStance stance = UNBLOCKED;

	void SoftLock(Console::ConsoleStream stream);
	void SoftLock(Console::ConsoleStream streamA, Console::ConsoleStream streamB);

	void unlock();

	void print(const char* format, const char* text, bool hard = true);
	void print_delayed();
};