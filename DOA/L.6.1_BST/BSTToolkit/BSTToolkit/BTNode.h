#pragma once

namespace BST
{
	template<typename T>
	class Node
	{
	public:
		Node(const T& i = T(), Node<T>* p = nullptr, Node<T>* l = nullptr, Node<T>* r = nullptr)
			: info(i), parent(p), left(l), right(r)
		{

		}

		T data;
		Node<T>* parent;
		Node<T>* left;
		Node<T>* right;
	};

}
