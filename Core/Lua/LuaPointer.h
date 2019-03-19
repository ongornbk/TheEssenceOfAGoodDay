#pragma once
#include "..\Src\corestd.h"

struct lua64int
{
	explicit lua64int(const _In_ int32_t f, const int32_t s) : first(f), second(s) {}

	int32_t first;
	int32_t second;
};

union LuaPointer32
{
	LuaPointer32(void* v)
	{
		ptr = v;
	}
	LuaPointer32(const uint32 i)
	{
		value = i;
	}

	void*  ptr;
	uint32 value;
	int32  lua;
};

union LuaPointer64
{
	LuaPointer64(void* v)
	{
		ptr = v;
	}
	LuaPointer64(const int32 first,const int32 second)
	{
		lua = lua64int(first, second);
	}
	LuaPointer64(const uint64 i)
	{
		value = i;
	}
	LuaPointer64(const lua64int l)
	{
		lua = l;
	}
	void* ptr;
	uint64   value;
	lua64int lua;
};

#if defined _M_IX86
typedef LuaPointer32 LuaPointer;
#elif defined _M_X64
typedef LuaPointer64 LuaPointer;
#endif