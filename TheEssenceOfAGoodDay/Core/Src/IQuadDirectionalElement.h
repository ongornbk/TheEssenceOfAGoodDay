#pragma once
#include "corestd.h"

template <class T>
class IQuadDirectionalElement
{
public:

	IQuadDirectionalElement()
	{
		left = nullptr;
		right = nullptr;
		top = nullptr;
		bottom = nullptr;
	}

	IQuadDirectionalElement(const T element)
	{
		left = nullptr;
		right = nullptr;
		top = nullptr;
		bottom = nullptr;
		data = element;
	}

	IQuadDirectionalElement(const T _element,
	IQuadDirectionalElement<T>* _left,
	IQuadDirectionalElement<T>* _right,
	IQuadDirectionalElement<T>* _top,
	IQuadDirectionalElement<T>* _bottom) : data(_element), left(_left), right(_right), top(_top), bottom(_bottom)
	{

	}

	
	T                            data;
	IQuadDirectionalElement<T>*  left;
	IQuadDirectionalElement<T>*  right;
	IQuadDirectionalElement<T>*  top;
	IQuadDirectionalElement<T>*  bottom;

private:

	


};