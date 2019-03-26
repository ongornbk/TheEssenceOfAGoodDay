#pragma once
#include "mmemory.h"

template <class T>
struct Node
{
	T     data;
	Node<T>* left;
	Node<T>* right;

	Node()
	{

	}

	~Node()
	{
		safe_delete(left);
		safe_delete(right);
	}

	void operator =(const T t)
	{
		data = t;
	}
};