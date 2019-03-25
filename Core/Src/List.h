#pragma once
#include "IStruct.h"

template <class T>
class List : public IStruct<T>
{
public:

	struct ListElement : public IElement<T>
	{

		ListElement(const T element)
		{
			data = element;
			next = nullptr;
			previous = nullptr;
		}

		~ListElement()
		{
			safe_delete(next);
		}


	};

	IElement<T>* __head;
	IElement<T>* __tail;

	uint32 __size;

	List()
	{
		__head = nullptr;
		__tail = nullptr;
		__size = 0u;
	}
	~List()
	{
		safe_delete(__head);
	}

	void push(const T element) override
	{
		if (__head)
		{
			__tail->next = new ListElement(element);
			__tail = __tail->next;
		}
		else
		{
			__head = new ListElement(element);
			__tail = __head;
		}
		__size++;
	}

	T& get() const override
	{
		assert(__head);
		return __head->data;
	}

	void pop()
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

};