#pragma once
#include <xmmintrin.h>


struct Float4
{
	__m128 data;

	Float4()
	{
		data = _mm_setzero_ps();
	}

	_Use_decl_annotations_
		Float4(_In_reads_(4) float A[4])
	{
		data = _mm_load_ps(A);
	}

	_Use_decl_annotations_
		inline void _vectorcall operator +=(const _In_ Float4 B) noexcept
	{
		data = _mm_add_ps(data, B.data);
	}

	_Use_decl_annotations_
		inline Float4 _vectorcall operator *(const _In_ float B) noexcept
	{
		Float4 fl4;
	fl4.data = _mm_mul_ps(data, _mm_set_ss(B));
	return fl4;
	}

};