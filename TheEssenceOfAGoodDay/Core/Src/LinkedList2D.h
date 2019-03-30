#pragma once
#include "mmemory.h"
#include "Array2D.h"
#include "IQuadDirectionalElement.h"
#include "Threading\ThreadPool.h"
#include "Threading\ThreadPoolHandle.h"

template<class T>
class LinkedList2D
{
public:

	LinkedList2D(const uint32 width, const uint32 height)
	{
		sizex = width;
		sizey = height;
		m_array = new Array2D<IQuadDirectionalElement<T>*>(sizex, sizey);

		IQuadDirectionalElement<T>*** data = m_array->data();

			for (uint32 x = 0u; x < sizex; x++)
				for (uint32 y = 0u; y < sizey; y++)
					data[x][y] = new IQuadDirectionalElement<T>();

			{
				IQuadDirectionalElement<T>* ele = data[0u][0u];
				ele->bottom = data[0u][1u];
				ele->left = nullptr;
				ele->right = data[1u][0u];
				ele->top = nullptr;
			}

			{
				IQuadDirectionalElement<T>* ele = data[0][sizey-1];
				ele->bottom = nullptr;
				ele->left = nullptr;
				ele->right = data[1u][sizey-1u];
				ele->top = data[0u][sizey - 2u];
			}

			{
				IQuadDirectionalElement<T>* ele = data[sizex - 1u][0u];
				ele->bottom = data[sizex - 1u][1u];
				ele->left = data[sizex - 2u][0u];
				ele->right = nullptr;
				ele->top = nullptr;
			}

			{
				IQuadDirectionalElement<T>* ele = data[sizex - 1u][sizey - 1u];
				ele->bottom = nullptr;
				ele->left = data[sizex - 2u][sizey - 1u];
				ele->right = nullptr;
				ele->top = data[sizex - 1u][sizey - 2u];
			}

			for (uint32 y = 1u; y < sizey - 1u; y++)
			{
				{
					IQuadDirectionalElement<T>* ele = data[0u][y];
					ele->bottom = data[0u][y + 1];
					ele->left = nullptr;
					ele->right = data[1u][y];
					ele->top = data[0u][y - 1u];
				}

				{
					IQuadDirectionalElement<T>* ele = data[sizex - 1u][y];
					ele->bottom = data[sizex - 1u][y + 1u];
					ele->left = data[sizex - 2u][y];
					ele->right = nullptr;
					ele->top = data[sizex - 1u][y - 1u];
				}
			}

			for (uint32 x = 1u; x < sizex - 1u; x++)
			{
				{
					IQuadDirectionalElement<T>* ele = data[x][0u];
					ele->bottom = data[x][1u];
					ele->left = data[x - 1u][0u];
					ele->right = data[x + 1u][0u];
					ele->top = nullptr;
				}

				{
					IQuadDirectionalElement<T>* ele = data[x][sizey - 1];
					ele->bottom = nullptr;
					ele->left = data[x - 1][sizey - 1];
					ele->right = data[x + 1][sizey - 1];
					ele->top = data[x][sizey - 2];
				}
			}

			for (uint32 x = 1u; x < sizex - 1u; x++)
			{
				for (uint32 y = 1u; y < sizey - 1u; y++)
				{
					IQuadDirectionalElement<T>* ele = data[x][y];
					ele->bottom = data[x][y+1u];
					ele->left = data[x-1u][y];
					ele->right = data[x+1u][y];
					ele->top = data[x][y-1u];
				}
			}

	}
	~LinkedList2D()
	{
		for (uint32 x = 0u; x < sizex; x++)
			for (uint32 y = 0u; y < sizey; y++)
				safe_delete((*m_array)[x][y]);

		safe_delete(m_array);
	}

	IQuadDirectionalElement<T>**& operator[](const uint32 element) const
	{
		return m_array[element];
	}

private:

	Array2D<IQuadDirectionalElement<T>*>* m_array;

	uint32 sizex;
	uint32 sizey;
};