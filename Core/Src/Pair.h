#pragma once
#include "corestd.h"

template <class A,class B>
struct Pair
{
	A first;
	B second;

	Pair() = default;

	Pair(A a, B b)
	{
		first = a;
		second = b;
	}
};