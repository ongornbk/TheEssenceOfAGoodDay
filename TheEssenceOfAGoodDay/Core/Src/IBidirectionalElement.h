#pragma once
#include "corestd.h"

template <class T>
class IBidirectionalElement
{
public:

	IBidirectionalElement(IBidirectionalElement<T>& ele) : data(ele->data), next(ele->next), previous(ele->previous){}

	T                          data;
	IBidirectionalElement<T>*  next;
	IBidirectionalElement<T>*  previous;

	static void SwapElements(IBidirectionalElement<T>* A, IBidirectionalElement<T>* B)
	{
//todo
	}
};