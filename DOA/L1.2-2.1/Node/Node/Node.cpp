#pragma once

#include"Node.h"

namespace LinkedList
{
	// Precondition: 
	// Postcondition: A new element containing 'data' is inserted at the head of the list pointed to by 'head'
	template<typename T>
	void Node<T>::headInsert(Node<T>*& headPtr, const T& data)
	{
		headPtr = new Node<T>(data, headPtr);
	}

	template<typename T>
	void Node<T>::headRemove(Node<T>*& headPtr)
	{
		Node<T>* tmp = headPtr;
		headPtr = headPtr->next;
		delete tmp;
	}

	template<typename T>
	void Node<T>::insert(Node<T>* prevPtr, const T & info)
	{
		Node<T>* tmp = prevPtr->next;
		prevPtr->next = new Node<T>(info);
		prevPtr->next->next = tmp;
		tmp = nullptr;
	}

	template<typename T>
	void Node<T>::remove(Node<T>* prevPtr)
	{
		Node<T>* tmp = prevPtr->next;
		prevPtr->next = prevPtr->next->next;
		delete tmp;
	}

	template<typename T>
	Node<T>* Node<T>::copy(Node<T>* sourcePtr)
	{
		Node* tmp = sourcePtr->next;
		sourcePtr->next = new Node(tmp->info);
		Node* tmp2 = sourcePtr->next;

		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
			tmp2->next = new Node<T>(tmp->info);
			tmp2 = tmp2->next;
		}
		tmp = nullptr;
		tmp2 = nullptr;
		return sourcePtr;
	}
}