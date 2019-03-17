#pragma once

#include <cassert>

typedef char               int8;
typedef short              int16;
typedef long               int32;
typedef long long          int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned long      uint32;
typedef unsigned long long uint64;

typedef void*              Handle;
typedef void(__cdecl*      Function)(void*);



class UInteger32
{
public:
	inline static uint32 Infinite()
	{
		return 0xFFFFFFFF;
	}
};