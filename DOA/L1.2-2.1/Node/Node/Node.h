#pragma once

namespace LinkedList
{
	template<typename T>
	class Node
	{
	public:
		Node(const T& i = T(), Node<T>* n = nullptr)
			: info(i), next(n)
		{

		}

		T info;
		Node<T>* next;
	};
	
}
