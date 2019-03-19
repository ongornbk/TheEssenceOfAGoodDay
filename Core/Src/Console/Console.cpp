#include "Console.h"
#include <conio.h>

//#define CONSOLE_DEBUG

namespace
{
	static Console* instance = nullptr;
	static String title(CONSOLE_NAME);
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
		print("Console created for %s\n", String(id).c_str());
#endif
	}
	else
	{
#ifdef CONSOLE_DEBUG
		print("CHandle created for %s\n", String(id).c_str());
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
			print("Console destroyed for %s\n", String(id).c_str());
#endif
			safe_delete(instance);
		}
		else
		{
#ifdef CONSOLE_DEBUG
			print("Opened CHandle destroyed for %s\n", String(id).c_str());
#endif
		}
	}
}

Console::Console()
{
AllocConsole();
SetConsoleTitle(title.c_str());
freopen("CONOUT$", "w", stdout);
HandleOut  = GetStdHandle(STD_OUTPUT_HANDLE);
HandleIn   = GetStdHandle(STD_INPUT_HANDLE);
delayedOut = new Queue<Pair<String,String>>();
cstance.store(OPEN);
}

Console::~Console()
{
cstance.store(CLOSED);
fclose(stdout);
FreeConsole();
instance = nullptr;
safe_delete(delayedOut);
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
		break;
	case DEL:
		del.lock();
		break;
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
		break;
	case DEL:
		del.unlock();
		break;
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
	print("%s", str.c_str(), true);
}

void ConsoleHandle::operator << (const char* str)
{
	print("%s", str, true);
}

void ConsoleHandle::operator<< (char ch)
{
	print("%s", String(ch).c_str(), true);
}

void ConsoleHandle::operator<< (int32 integer)
{
	print("%s", String(integer).c_str(), true);
}

void ConsoleHandle::operator < (String str)
{
	print("%s",str.c_str(), false);
}

void ConsoleHandle::operator < (const char* str)
{
	print("%s", str, false);
}

void ConsoleHandle::operator< (char ch)
{
	print("%s", String(ch).c_str(), false);
}

void ConsoleHandle::operator< (int32 integer)
{
	print("%s", String(integer).c_str(),false);
}


void ConsoleHandle::operator>>(String& str)
{
	int32 key{};
	char escape = true;
	instance->lock(Console::ConsoleStream::CIN);
	instance->lock(Console::ConsoleStream::COUT);
	Console::ConsoleStance lcs = instance->cstance.load();
	instance->cstance.store(Console::ConsoleStance::RECEIVING);
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

			printf_s("%c",key);

			str += (char)key;
		}
		}
	}

	instance->cstance.store(lcs);
	instance->unlock(Console::ConsoleStream::CIN);
	instance->unlock(Console::ConsoleStream::COUT);
	print_delayed();

}

void ConsoleHandle::operator >(String & str)
{
	int32 key{};
	char escape = true;
	instance->lock(Console::ConsoleStream::CIN);
	instance->lock(Console::ConsoleStream::COUT);
	Console::ConsoleStance lcs = instance->cstance.load();
	instance->cstance.store(Console::ConsoleStance::RECEIVING);
	printf_s("%s", str.c_str());
	str.clear();
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

			printf_s("%c", key);

			str += (char)key;
		}
		}
	}

	instance->cstance.store(lcs);
	instance->unlock(Console::ConsoleStream::CIN);
	printf_s("%c",endl);
	instance->unlock(Console::ConsoleStream::COUT);
	print_delayed();
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
			print("Console manually closed by %s\n", String(id).c_str());
#endif
			safe_delete(instance);
		}
		else
		{
#ifdef CONSOLE_DEBUG
			print("Handle closed by %s\n", String(id).c_str());
#endif
		}
	}
}

void ConsoleHandle::pause()
{
	instance->lock(Console::ConsoleStream::CIN);
	Console::ConsoleStance lcs = instance->cstance.load();
	instance->cstance.store(Console::ConsoleStance::PAUSED);
	(void)getch();
	instance->cstance.store(lcs);
	instance->unlock(Console::ConsoleStream::CIN);
	print_delayed();
}

void ConsoleHandle::SoftLock(Console::ConsoleStream stream)
{
	if (stance == HandleStance::UNBLOCKED)
	{
		instance->lock(stream);
		stance = HandleStance::BLOCKED;
	}
}


void ConsoleHandle::unlock()
{
	assert(stance == HandleStance::BLOCKED);
	stance = HandleStance::UNBLOCKED;
}

void ConsoleHandle::SoftLock(Console::ConsoleStream streamA, Console::ConsoleStream streamB)
{
	assert(streamA != streamB);
	if (stance == HandleStance::UNBLOCKED)
	{
		instance->lock(streamA);
		instance->lock(streamB);
		stance = HandleStance::BLOCKED;
	}
}

void ConsoleHandle::SetTitle(String str)
{
	instance->lock(Console::ConsoleStream::CON);
	title = str;
	SetConsoleTitle(str.c_str());
	instance->unlock(Console::ConsoleStream::CON);
}

void ConsoleHandle::print(const char* format, const char* text,bool hard)
{
	switch (instance->cstance.load())
	{
	case Console::ConsoleStance::OPEN:
	{
		instance->cstance.store(Console::ConsoleStance::PRINTING);
		SoftLock(Console::ConsoleStream::COUT);
		printf_s(format, text);
		if (hard)
		{
			instance->unlock(Console::ConsoleStream::COUT);
			stance = HandleStance::UNBLOCKED;
		}
		instance->cstance.store(Console::ConsoleStance::OPEN);
		break;
	}
	case Console::ConsoleStance::PRINTING:
	{
		SoftLock(Console::ConsoleStream::COUT);
		printf_s(format, text);
		if (hard)
		{
			instance->unlock(Console::ConsoleStream::COUT);
			stance = HandleStance::UNBLOCKED;
		}
		break;
	}
	case Console::ConsoleStance::RECEIVING:
	{
		SoftLock(Console::ConsoleStream::DEL);
		instance->delayedOut->push(Pair<String, String>(String(format), String(text)));
		if (hard)
		{
			instance->unlock(Console::ConsoleStream::DEL);
			stance = HandleStance::UNBLOCKED;
		}
		break;
	}
	case Console::ConsoleStance::PAUSED:
	{
		SoftLock(Console::ConsoleStream::DEL);
		instance->delayedOut->push(Pair<String,String>(String(format), String(text)));
		if (hard)
		{
			instance->unlock(Console::ConsoleStream::DEL);
			stance = HandleStance::UNBLOCKED;
		}
		break;
	}
	case Console::ConsoleStance::CLOSED:
	{
		break;
	}

	}

}

void ConsoleHandle::print_delayed()
{
	SoftLock(Console::ConsoleStream::COUT, Console::ConsoleStream::DEL);
	auto del = instance->delayedOut;
	pop_each(del)
	{
		printf_s(del->get().first.c_str(), del->get().second.c_str());
	}
	instance->unlock(Console::ConsoleStream::COUT);
	instance->unlock(Console::ConsoleStream::DEL);
	unlock();
}