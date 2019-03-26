#pragma once
#include "mmemory.h"

class Actor
{
public:

	virtual void Render() = 0;
	virtual void Tick(const float _In_ dt = 0) noexcept = 0;
	virtual void Release() = 0;
	virtual void BeginOverlap(const Actor* second);

protected:

	uint32 m_index;
	uint32 m_vector;

};