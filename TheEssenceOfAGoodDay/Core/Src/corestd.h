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
#include <algorithm>
#include <sal.h>

#include <Windows.h>

using std::atomic;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::shared_mutex;
using std::condition_variable;
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
		ptr->Release();
		ptr = nullptr;
	}
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

#define _for_each(istruct_type) for(auto ele = istruct_type.front(); ele != nullptr; ele = ele->next)

#define _for_each_reverse(istruct_type) for(auto ele = istruct_type.end();ele != nullptr; ele = ele->previous)

#define _for_each_pair(istruct_type) for(auto ele = istruct_type->front(); ele != nullptr; ele = ele->next)

#define _pop_each(istruct_type) for(;istruct_type->empty() == false;istruct_type->pop())