#pragma once
#include "Thread.h"
#include "Queue.h"
#include "Vector.h"


struct Task
{
	Function foo;
	void*    arg;

	void execute()
	{
		foo(arg);
	}
};

class ThreadPool
{

	

	bool                 _running;
	Queue<Task>      _taskQueue;
	atomic<size_t>       _taskNum;
	mutex                _mutex;
	Vector<Thread*>      _threads;

public:
	ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
	virtual ~ThreadPool();
	void push(Function work);
	void push(Function work, void* argument);
	void clear();
	void wait();

	friend void ThreadLoop(void* pt);
};

