#include "ThreadPool.h"

ThreadPool* ThreadPool::m_instance = nullptr;

static void _cdecl ThreadLoop(void* pt)
{
	ThreadPool* pool = (ThreadPool*)pt;


	while (pool->_running.load()) {
		unique_lock <mutex> lk(pool->_mutex);
		if (!pool->_taskQueue.empty()) {
			Task task = pool->_taskQueue.get();
			pool->_taskQueue.pop();
			pool->_mutex.unlock();
			task.execute();
			pool->_taskNum--;
		}
		else {
			pool->_cv.wait(lk);
		}
	}
}

ThreadPool::ThreadPool(size_t num_threads) : _taskNum(0)
{
	_running.store(true);
	m_instance = this;
	_threads.reserve(num_threads);
	for (size_t i = 0; i < num_threads; i++) {
		_threads.push_back(Thread(ThreadLoop, NULL, this));
	}

}

	ThreadPool::~ThreadPool()
{
		m_instance = nullptr;
		_running.store(false);
		_cv.notify_all();
		for (auto&& t : _threads) t.join();
}

void ThreadPool::push(Function work)
{
	Task task;
	task.foo = work;
	task.arg = nullptr;

	unique_lock<mutex> lk(_mutex);
		_taskQueue.push(task);
		_taskNum++;
		_cv.notify_one();
}

void ThreadPool::push(Function work,void* argument)
{
	Task task;
	task.foo = work;
	task.arg = argument;

	unique_lock<mutex> lk(_mutex);
	_taskQueue.push(task);
	_taskNum++;
	_cv.notify_one();
}

void ThreadPool::clear()
{
	unique_lock<mutex> lk(_mutex);
	_taskNum -= _taskQueue.size();
}

void ThreadPool::wait()
{
	while (_taskNum.load() > 0) {
		std::this_thread::yield();
	}
}
	