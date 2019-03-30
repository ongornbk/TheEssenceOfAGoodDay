#pragma once
#include "ThreadPool.h"

struct ThreadPoolHandle
{
	ThreadPoolHandle();
	~ThreadPoolHandle();

	void operator << (tpTask task);

	ThreadPool* operator ->();
	void wait();

private:

	ThreadPool* pool;
};