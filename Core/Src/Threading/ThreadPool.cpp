#include "ThreadPool.h"

ThreadPool* ThreadPool::m_instance = nullptr;

static void _cdecl ThreadLoop(void* pt)
{
	ThreadPool* pool = (ThreadPool*)pt;

	while (pool->_running) {
		pool->_mutex.lock();
		if (!pool->_taskQueue.empty()) {
			Task task = pool->_taskQueue.front();
			pool->_taskQueue.pop();
			pool->_mutex.unlock();
			task.execute();
			pool->_taskNum--;
		}
		else {
			pool->_mutex.unlock();
			std::this_thread::yield();
		}
	}
}

ThreadPool::ThreadPool(size_t num_threads) : _running(true), _taskNum(0)
{
	m_instance = this;
	auto thread_loop = [](void* pt) {

		
	};
	_threads.reserve(num_threads);
	for (size_t i = 0; i < num_threads; i++) {
		Thread* t = new Thread(ThreadLoop, NULL, this);
	}

}

	ThreadPool::~ThreadPool()
{
		m_instance = nullptr;
		_running = false;
		for (auto&& t : _threads) {
			if (t)
			{
				t->join();
				delete t;
				t = nullptr;
			}
		}
}

void ThreadPool::push(Function work)
{
	Task task;
	task.foo = work;
	task.arg = nullptr;

		_mutex.lock();
		_taskQueue.push(task);
		_taskNum++;
		_mutex.unlock();
}

void ThreadPool::push(Function work,void* argument)
{
	Task task;
	task.foo = work;
	task.arg = argument;

	_mutex.lock();
	_taskQueue.push(task);
	_taskNum++;
	_mutex.unlock();
}

void ThreadPool::clear()
{
	_mutex.lock();
	_taskNum -= _taskQueue.size();
	_mutex.unlock();
}

void ThreadPool::wait()
{
	while (_taskNum.load() > 0) {
		std::this_thread::yield();
	}
}
	