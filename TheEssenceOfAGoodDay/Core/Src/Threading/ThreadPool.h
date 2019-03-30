
#pragma once
#include "..\mmemory.h"
#include "..\Queue.h"

typedef std::function<void(void)> tpTask;


class ThreadPool {
private:
	atomic<bool> _running;
	Queue<tpTask> _taskQueue;
	condition_variable cv;
	atomic<size_t> _taskNum;
	mutex _mutex;
	vector<std::thread> _threads;
public:
	ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
	~ThreadPool();
	void push(tpTask work);
	void clear();
	void wait();
	static bool isActive() noexcept;

	static ThreadPool* m_instance;
};