#pragma once
#include "IStruct.h"

template <class T>
class Queue : public IStruct<T>
{

public:

	struct QueueElement : public IElement<T>
	{

		QueueElement(const T element)
		{
			data = element;
			next = nullptr;
		}

		~QueueElement()
		{
			safe_delete(next);
		}

	};



	IElement<T>* __head;
	IElement<T>* __tail;

	uint32 __size;

	Queue()
	{
		__head = nullptr;
		__tail = nullptr;
		__size = 0u;
	}
	~Queue()
	{
		safe_delete(__head);
	}

	void push(const T element) override
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

	T& get() const override
	{
		assert(__head);
		return __head->data;
	}

	void pop() override
	{
		assert(__head);
		IElement<T>* pop = __head;
		__head = __head->next;
			pop->next = nullptr;
			delete pop;
			__size--;
	}

	uint32 size() const override
	{
		return __size;
	}

	bool empty() const override
	{
		if (__size)
			return false;
		else return true;
	}

	IElement<T>* front() const override
	{
		return __head;
	}

	void clear() override
	{
		__size = 0u;
		safe_delete(__head);
	}

};