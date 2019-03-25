#pragma once
#include "corestd.h"

template <class T>
class IElement
{
public:
	T             data;
	IElement<T>*  next;
};

