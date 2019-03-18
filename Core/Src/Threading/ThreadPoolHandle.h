#pragma once
#include "ThreadPool.h"

struct ThreadPoolHandle
{
	ThreadPoolHandle();
	~ThreadPoolHandle();


	void operator << (Function task);
	ThreadPool* operator ->();
	void wait();

private:

	ThreadPool* pool;
};