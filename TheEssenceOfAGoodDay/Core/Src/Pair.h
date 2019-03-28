#pragma once
#include "mmemory.h"
#include <type_traits>

template <class A,class B>
struct Pair
{
	A first{};
	B second{};

	Pair()
	{

	}

	Pair(A a) : first(a) {}

	Pair(A a, B b) : first(a), second(b) {}

	~Pair()
	{

	}

	bool operator ==(const Pair<A, B>& b) const
	{
		return (this->first == b.first) && (this->second == b.second);
	}

	void operator = (const B b)
	{
		second = b;
	}

};