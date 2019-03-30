#include "ThreadPoolHandle.h"

ThreadPoolHandle::ThreadPoolHandle()
{
	pool = ThreadPool::m_instance;
}

ThreadPoolHandle::~ThreadPoolHandle()
{
	pool->wait();
}

void ThreadPoolHandle::operator<<(tpTask task)
{
	pool->push(task);
}

ThreadPool * ThreadPoolHandle::operator->()
{
	return pool;
}

void ThreadPoolHandle::wait()
{
	pool->wait();
}