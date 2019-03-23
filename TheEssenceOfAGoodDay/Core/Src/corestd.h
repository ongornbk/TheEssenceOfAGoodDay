#pragma once
#define NOMINMAX
#include <cassert>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <string>
#include <fstream>
#include <vector>
#include <sal.h>
#include <algorithm>

#include <Windows.h>

using std::atomic;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::shared_mutex;
using std::string;
using std::fstream;
using std::ifstream;
using std::vector;

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

template <class T>
inline void safe_delete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <class T>
inline void safe_release(T& ptr)
{
	if (ptr)
	{
		ptr->release();
		ptr = nullptr;
	}
}

template <class _Out_ ReturnType, class _In_ Type>
inline ReturnType& memory_cast(const Type& obj)
{
	return *(ReturnType*)(obj);
}

class UInteger32
{
public:
	inline static uint32 Infinite()
	{
		return 0xFFFFFFFF;
	}
};

#define endl String('\n')
#define CONSOLE_NAME "The Essence Of A Good Day"