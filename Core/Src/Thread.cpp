#include "Thread.h"

#include <process.h>
#include <Windows.h>


Thread::Thread(Function foo,uint32 startAddress,void* argList)
{
	assert(foo);
	thread = (Handle)_beginthread(foo, startAddress, argList);
}

void Thread::join()
{
	WaitForSingleObject(thread, UInteger32::Infinite());
}
