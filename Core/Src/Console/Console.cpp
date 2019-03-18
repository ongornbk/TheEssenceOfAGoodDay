#include "Console.h"
#include <conio.h>

namespace
{
	static Console* instance = nullptr;
	atomic<uint32> uses(0u);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

ConsoleHandle::ConsoleHandle()
{
	uses++;
	id = uses.load();
	if (!instance)
	{
		instance = new Console();
#ifdef CONSOLE_DEBUG
		instance->lock(Console::ConsoleStream::COUT);
		printf_s("Console created for %d\n", id);
		instance->unlock(Console::ConsoleStream::COUT);
#endif
	}
	else
	{
#ifdef CONSOLE_DEBUG
		instance->lock(Console::ConsoleStream::COUT);
		printf_s("CHandle created for %d\n", id);
		instance->unlock(Console::ConsoleStream::COUT);
#endif
	}

}

ConsoleHandle::~ConsoleHandle()
{
	if (!closed)
	{
		uses--;
		if (uses.load(std::memory_order::memory_order_seq_cst) == 0u)
		{
#ifdef CONSOLE_DEBUG
			instance->lock(Console::ConsoleStream::COUT);
			printf_s("Console destroyed for %d\n", id);
			instance->unlock(Console::ConsoleStream::COUT);
#endif
			safe_delete(instance);
		}
		else
		{
#ifdef CONSOLE_DEBUG
			instance->lock(Console::ConsoleStream::COUT);
			printf_s("Opened CHandle destroyed for %d\n", id);
			instance->unlock(Console::ConsoleStream::COUT);
#endif
		}
	}
}

Console::Console()
{
AllocConsole();
SetConsoleTitle(CONSOLE_NAME);
freopen("CONOUT$", "w", stdout);
HandleOut  = GetStdHandle(STD_OUTPUT_HANDLE);
HandleIn   = GetStdHandle(STD_INPUT_HANDLE);
}

Console::~Console()
{
fclose(stdout);
FreeConsole();
instance = nullptr;
}

void Console::lock(ConsoleStream cs)
{
	switch (cs)
	{
	case CIN:
		in.lock();
		break;
	case COUT:
		out.lock();
		break;
	case CON:
		con.lock();
	}
}
void Console::unlock(ConsoleStream cs)
{
	switch (cs)
	{
	case CIN:
		in.unlock();
		break;
	case COUT:
		out.unlock();
		break;
	case CON:
		con.unlock();
	}
}

void Console::lock_shared(ConsoleStream cs)
{
	switch (cs)
	{
	case CON:
		con.lock_shared();
	}
}
void Console::unlock_shared(ConsoleStream cs)
{
	switch (cs)
	{
	case CON:
		con.unlock_shared();
	}
}

void Console::UpdatePosition()
{
	SetConsoleCursorPosition(HandleOut, pos);
}

void Console::Backspace()
{
	GoBack();
	printf_s("%c",' ');
	UpdatePosition();
}

void Console::GoBack()
{
	pos = GetConsoleCursorPosition(HandleOut);
	if (pos.X != 0)
	{
		pos.X--;
	}
	UpdatePosition();
}

void ConsoleHandle::operator << (String str)
{
	instance->lock(Console::ConsoleStream::COUT);
	printf_s("%s",str.c_str());
	instance->unlock(Console::ConsoleStream::COUT);
}

void ConsoleHandle::operator << (const char* str)
{
	instance->lock(Console::ConsoleStream::COUT);
	printf_s("%s", str);
	instance->unlock(Console::ConsoleStream::COUT);
}

void ConsoleHandle::operator<< (char ch)
{
	instance->lock(Console::ConsoleStream::COUT);
	printf_s("%c",ch);
	instance->unlock(Console::ConsoleStream::COUT);
}

void ConsoleHandle::operator<< (int32 integer)
{
	instance->lock(Console::ConsoleStream::COUT);
	printf_s("%d", integer);
	instance->unlock(Console::ConsoleStream::COUT);
}

void ConsoleHandle::operator>>(String& str)
{
	int32 key{};
	char escape = true;
	instance->lock(Console::ConsoleStream::CIN);
	while (escape)
	{
		key = getch();
		switch (key)
		{
		case '\r':
		{
			escape = false;
			break;
		}
		case '\b':
		{
			instance->lock(Console::ConsoleStream::CON);
			instance->Backspace();
			instance->unlock(Console::ConsoleStream::CON);
			break;
		}

		default:
		{
			instance->lock(Console::ConsoleStream::COUT);
			printf_s("%c",key);
			instance->unlock(Console::ConsoleStream::COUT);
			str += (char)key;
		}
		}
	}
	instance->unlock(Console::ConsoleStream::CIN);

}

void ConsoleHandle::close()
{
	assert(!closed);
	if (!closed)
	{
		closed = true;
		uses--;
		if (uses.load(std::memory_order::memory_order_seq_cst) == 0u)
		{
#ifdef CONSOLE_DEBUG
			instance->lock(Console::ConsoleStream::COUT);
			printf_s("Console manually closed by %d\n", id);
			instance->unlock(Console::ConsoleStream::COUT);
#endif
			safe_delete(instance);
		}
		else
		{
#ifdef CONSOLE_DEBUG
			instance->lock(Console::ConsoleStream::COUT);
			printf_s("Handle closed by %d\n", id);
			instance->unlock(Console::ConsoleStream::COUT);
#endif
		}
	}
}

void ConsoleHandle::pause()
{
	instance->lock(Console::ConsoleStream::CIN);
	(void)getch();
	instance->unlock(Console::ConsoleStream::CIN);
}