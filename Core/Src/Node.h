#pragma once
#include "corestd.h"

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
};