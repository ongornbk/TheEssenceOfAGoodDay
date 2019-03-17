#include "Thread.h"

#include <process.h>


Thread::Thread(Function foo,uint32 startAddress,void* argList)
{
	assert(foo);
	thread = (Handle)_beginthread(foo, startAddress, argList);
}

Thread::~Thread()
{
	if(thread)
	WaitForSingleObject(thread, UInteger32::Infinite());
	thread = nullptr;
}

void Thread::join()
{
	WaitForSingleObject(thread, UInteger32::Infinite());
	thread = nullptr;
}
