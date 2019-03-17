#pragma once

#include <cassert>
#include <atomic>
#include <mutex>

#include <Windows.h>

using std::atomic;
using std::mutex;

typedef signed char        int8;
typedef signed short       int16;
typedef signed long        int32;
typedef signed long long   int64;

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