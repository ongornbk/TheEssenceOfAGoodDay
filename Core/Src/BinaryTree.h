#pragma once
#include "Node.h"


//#define BINARYTREE_DEBUG
#ifdef BINARYTREE_DEBUG
#include "Console\Console.h"
#endif // BINARYTREE_DEBUG


template <class T>
class BinaryTree
{

protected:

	bool(_cdecl* m_foo)(const T& A, const T& B);

	Node<T>* root{};

	uint32 __size = 0u;

public:

	BinaryTree(bool(_cdecl* foo)(const T& A, const T& B)) : m_foo(foo)
	{ 
		assert(foo);
	}
	virtual  ~BinaryTree()
	{
		safe_delete(root);
	}

	void push(const T element)
	{
		__size++;
		if (root != nullptr)
			push(element, root);
		else
		{
			root = new Node<T>();
			root->data = element;
			root->left = nullptr;
			root->right = nullptr;
		}
	}
	void push(const T element, Node<T>* node)
	{
		const bool direction = m_foo(element, node->data);

		if (direction)
		{
			if (node->left != nullptr)
				push(element, node->left);
			else
			{
				node->left = new Node<T>();
				node->left->data = element;
				node->left->left = nullptr;
				node->left->right = nullptr;
			}
		}
		else
		{
			if (node->right != nullptr)
				push(element, node->right);
			else
			{
				node->right = new Node<T>();
				node->right->data = element;
				node->right->left = nullptr;
				node->right->right = nullptr;
			}
		}
	}

	Node<T>*& find(const T element,Node<T>* &node)
	{
		if (node != nullptr)
		{
			if (element == node->data)
				return node;
			if (m_foo(element,node->data))
				return find(element, node->left);
			else
				return find(element, node->right);
		}
		else return node;
	}

	Node<T>*& find(const T element, Node<T>* &node,bool(_cdecl* foo)(const T& A, const T& B))
	{
#ifdef BINARYTREE_DEBUG
		{
			ConsoleHandle con;
			con < "Node<T>* find(const T element, Node<T>* &node,bool(_cdecl* foo)(const T& A, const T& B)) ::: CALLED";
			con < endl;
			con < "element = ";
			con.format("%016llX");
			con < memory_cast<uint64>(&element);
			con.format();
			con < " node = ";
			con.format("%016llX");
			con < memory_cast<uint64>(&node);
			con.format();
			con < " foo = ";
			con.format("%016llX");
			con < memory_cast<uint64>(foo);
			con.format();
			con << endl;
		}
#endif // BINARYTREE_DEBUG

		
		if (node != nullptr)
		{
			if (foo(element,node->data))
				return node;
			if (m_foo(element, node->data))
				return find(element, node->left,foo);
			else
				return find(element, node->right,foo);
		}
		else return node;
	}

	Node<T>* find(const T element)
	{
		return find(element, root);
	}

	void read(Node<T>* node, vector<T>& vec,uint32& count)
	{
		if (node == nullptr) return;
		read(node->left, vec, count);
		vec[count] = node->data;
		count++;
		read(node->right, vec, count);
	}

	void read(vector<T>& vec)
	{
		vec.resize(__size);
		
		uint32 count = 0u;
		if (root == nullptr) return;
		read(root->left, vec, count);
		vec[count] = root->data;
		count++;
		read(root->right, vec, count);
	}

};