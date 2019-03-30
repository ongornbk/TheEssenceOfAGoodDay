#pragma once
#include "IStruct.h"

template <class T>
class Stack : public IStruct<T>
{



public:

	struct StackElement : public IElement<T>
	{

		StackElement(const T element)
		{
			data = element;
			next = nullptr;
		}

		~StackElement()
		{
			safe_delete(next);
		}

	};

	IElement<T>*  __top;

	uint32        __size;

	Stack()
	{
		__top = nullptr;
		__size = 0;
	}

	~Stack()
	{
		safe_delete(__top);
	}

	void push(const T element) override
	{
		if (__top)
		{
			IElement<T>* niu = new StackElement(element);
			niu->next = __top;
			__top = niu;
		}
		else
		{
			__top = new StackElement(element);
		}
		__size++;
	}

	T& get() const override
	{
		assert(__top);
		return __top->data;
	}

	void pop()
	{
		assert(__top);
		IElement<T>* pop = __top;
		__top = __top->next;
		pop->next = nullptr;
		delete pop;
		__size--;
	}

	IElement<T>* front() const override
	{
		assert(__top);
		return __top;
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

	void clear() override
	{
		__size = 0u;
		safe_delete(__top);
	}

};