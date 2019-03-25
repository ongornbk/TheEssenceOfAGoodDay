#pragma once
#include "corestd.h"

template <class T>
class IBidirectionalElement
{
public:
	T                          data;
	IBidirectionalElement<T>*  next;
	IBidirectionalElement<T>*  previous;
};