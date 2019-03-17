#pragma once
#include "corestd.h"

template <class T>
class Queue
{

public:

	struct QueueElement
	{
		T             data;
		QueueElement* next;

		QueueElement(const T element)
		{
			data = element;
			next = nullptr;
		}

		~QueueElement()
		{
			if (next)
			{
				delete next;
				next = nullptr;
			}
		}

	};



	QueueElement* __head;
	QueueElement* __tail;

	uint32 __size;

	Queue()
	{
		__head = nullptr;
		__tail = nullptr;
		__size = 0u;
	}
	~Queue()
	{
		if (__head)
		{
			delete __head;
			__head = nullptr;
		}
	}

	void push(const T element)
	{
		if (__head)
		{
			__tail->next = new QueueElement(element);
			__tail = __tail->next;
		}
		else
		{
			__head = new QueueElement(element);
			__tail = __head;
		}
		__size++;
	}

	T front()
	{
		assert(__head);
		return __head->data;
	}

	void pop()
	{
		assert(__head);
		QueueElement* pop = __head;
		__head = __head->next;
			pop->next = nullptr;
			delete pop;
			__size--;
	}

	uint32 size()
	{
		return __size;
	}

	bool empty()
	{
		if (__size)
			return false;
		else return true;
	}

	QueueElement* head()
	{
		return __head;
	}

};