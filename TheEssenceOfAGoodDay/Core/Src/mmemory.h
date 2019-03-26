#pragma once
#include "corestd.h"

template <class _Out_ ReturnType, class _In_ Type>
inline ReturnType& memory_cast(const Type& obj)
{
	return *(ReturnType*)(obj);
}

template <class _Out_ ReturnType,class _In_ Type>
inline ReturnType* mmalloc(const Type nitems)
{
	return (ReturnType*)malloc((nitems) * sizeof(ReturnType));
}

template <class ReturnType,class A, class _In_ Type>
inline ReturnType* mrealloc(A& ptr,const Type nitems)
{
	return (ReturnType*)realloc(ptr,(nitems) * sizeof(ReturnType));
}

template <class A>
inline void mfree(A& ptr)
{
	return free(ptr);
}