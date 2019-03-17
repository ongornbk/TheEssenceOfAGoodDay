#pragma once
#include "corestd.h"


class Thread
{
	Handle thread;

public:

	Thread(Function foo, uint32 startAddress, void* argList);

	void join();

};