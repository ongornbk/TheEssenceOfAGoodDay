#pragma once
#include "IElement.h"

#define _for_each(istruct_type,type) for(IElement<type>* ele = istruct_type->front(); ele != nullptr; ele = ele->next)

#define _for_each_pair(istruct_type,A,B) for(IElement<Pair<A,B>>* ele = istruct_type->front(); ele != nullptr; ele = ele->next)

#define _pop_each(istruct_type) for(;istruct_type->empty() == false;istruct_type->pop())

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


