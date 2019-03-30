#pragma once
#include "mmemory.h"

template <class T>
class Array
{
public:

	explicit Array()
	{
		m_size = 0u;
		m_capacity = 2u;
		m_data = mmalloc<T>(m_capacity);
	}
	Array(const uint32 capacity)
	{
		assert(capacity);
		m_size = 0u;
		m_capacity = capacity;
		m_data = mmalloc<T>(m_capacity);
	}

	~Array()
	{
		mfree(m_data);
	}

	T* begin() const
	{
		return m_data;
	}
	T* end() const
	{
		return (m_data + m_size);
	}
	T& operator[](const uint32 element) const
	{
		assert(element < m_size);
		return *(m_data + element);
	}

	T& at(const uint32 element) const
	{
		assert(element < m_size);
		return *(m_data + element);
	}

	void resize(const uint32 size = m_capacity)
	{
		m_size = size;
		if (m_size > m_capacity)
		{
			m_capacity = m_size;
			m_data = (T*)realloc(m_data, sizeof(T)*m_capacity);
		}
	}

	void reserve(const uint32 capacity)
	{
		if (capacity > m_capacity)
		{
			m_data = mrealloc<T>(m_data, capacity);
		}
	}

	void push_back(T element)
	{
		m_size++;
		if (m_size >= m_capacity)
		{
			m_capacity *= 2u;
			m_data = mrealloc<T>(m_data, m_capacity);
		}
		m_data[m_size - 1u] = element;
	}



	T* data() const
	{
		return m_data;
	}

	const uint32 size() const
	{
		return m_size;
	}

	const uint32 capacity() const
	{
		return m_capacity;
	}

	const bool empty() const
	{
		if (m_size) return false;
		else return true;
	}

	void clear()
	{
		m_size = 0u;
	}

private:

	T* m_data;
	uint32 m_capacity;
	uint32 m_size;

};

template <class T>
class Array_view
{
	T* m_data;
	uint32 m_size;
public:

	explicit Array_view(const T* data, uint32 size)
	{
		m_data = data;
		m_size = size;
	}

	explicit Array_view(T* begin, T* end)
	{
		m_size = (uint32)(end - begin);
		m_data = begin;
	}

	~Array_view()
	{

	}
	T* begin()
	{
		return m_data;
	}
	T* end()
	{
		return (m_data + m_size);
	}
	T& operator[](uint32 element)
	{
		assert(element < m_size);
		return *(m_data + element);
	}

	uint32 size()
	{
		return m_size;
	}
};