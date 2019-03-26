#pragma once
#include "mmemory.h"

template <class T>
class IElement
{
public:
	T             data;
	IElement<T>*  next;
};

