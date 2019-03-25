#pragma once
#include "IElement.h"

template<class T>
class IStruct
{
public:
	virtual uint32       size()  const = 0;
	virtual bool         empty() const = 0;
	virtual IElement<T>* front() const = 0;
	virtual T&           get()   const = 0;

	virtual void         pop()                 = 0;
	virtual void         push(const T element) = 0;



};