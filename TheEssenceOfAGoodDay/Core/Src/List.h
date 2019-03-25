#pragma once
#include "IBidirectionalStruct.h"

template <class T>
class List : public IBidirectionalStruct<T>
{
public:

	struct ListElement : public IBidirectionalElement<T>
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

	IBidirectionalElement<T>* __head;
	IBidirectionalElement<T>* __tail;

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

	void push_end(const T element) override
	{
		if (__head)
		{
			__tail->next = new ListElement(element);
			IBidirectionalElement<T>* prev = __tail;
			__tail = __tail->next;
			__tail->previous = prev;
		}
		else
		{
			__head = new ListElement(element);
			__tail = __head;
		}
		__size++;
	}

	void push_front(const T element) override
	{
		if (__head)
		{
			__head->previous = new ListElement(element);
			IBidirectionalElement<T>* next = __head;
			__head = __head->previous;
			__head->next = next;
		}
		else
		{
			__head = new ListElement(element);
			__tail = __head;
		}
		__size++;
	}

	T& get_front() const override
	{
		assert(__head);
		return __head->data;
	}

	T& get_end() const override
	{
		assert(__tail);
		return __tail->data;
	}

	void pop_front()
	{
		assert(__head);
		IBidirectionalElement<T>* pop = __head;
		__head = __head->next;
		pop->next = nullptr;
		delete pop;
		__size--;
	}

	void pop_end()
	{
		assert(__tail);
		IBidirectionalElement<T>* pop = __tail;
		__tail = __tail->previous;
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

	IBidirectionalElement<T>* front() const override
	{
		return __head;
	}

	IBidirectionalElement<T>* end() const override
	{
		return __tail;
	}

};