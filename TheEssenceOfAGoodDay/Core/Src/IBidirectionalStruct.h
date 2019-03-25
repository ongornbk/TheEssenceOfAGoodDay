#pragma once
#include "IBidirectionalElement.h"

template<class T>
class IBidirectionalStruct
{
public:
	virtual uint32                    size()  const = 0;
	virtual bool                      empty() const = 0;

	virtual IBidirectionalElement<T>* front() const = 0;
	virtual IBidirectionalElement<T>* end()   const = 0;

	virtual T&                        get_front()   const = 0;
	virtual T&                        get_end()   const = 0;
	virtual void                      pop_front() = 0;
	virtual void                      push_front(const T element) = 0;
	virtual void                      pop_end() = 0;
	virtual void                      push_end(const T element) = 0;


};
