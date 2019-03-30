#pragma once
#include "mmemory.h"

template <class T>
class Array2D
{
public:

	Array2D(const uint32 xsize, const uint32 ysize)
	{
		assert(xsize&&ysize);
		_sizex = xsize;
		_sizey = ysize;
		_data = mmalloc<T*>(xsize);
		for (uint32 y = 0u; y < ysize; y++)
		{
			_data[y] = mcalloc<T>(ysize);
		}
	}

	~Array2D()
	{
		for (uint32 y = 0u; y < _sizey; y++)
		{
			mfree(_data[y]);
		}
		mfree(_data);
	}

	T** begin() 
	{
		return _data;
	}
	T** end() const
	{
		return (_data + _sizex);
	}

	T** data() const
	{
		return _data;
	}

	T*& operator[](const uint32 element) const
	{
		assert(element < _sizex);
		return *(_data + element);
	}

	const uint32 sizex() const
	{
		return _sizex;
	}

	const uint32 sizey() const
	{
		return _sizey;
	}

private:

	T** _data;
	uint32 _sizex;
	uint32 _sizey;

};