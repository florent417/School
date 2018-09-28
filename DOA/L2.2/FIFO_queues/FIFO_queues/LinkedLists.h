#pragma once
#include "Node.h"
#include <iostream>

namespace LinkedList
{
	template<typename T>
	// Precondition: headPtr points to the head of a list
			// Postcondition: Info has been inserted at the head of the list, and headPtr is updated
	void headInsert(Node<T>* &headPtr, const T &info);
	
	template<typename T>
	// Precondition: headPtr points to the head of a list
	// Postcondition: The head element has been removed and headPtr is updated to point to the new
	// head element
	void headRemove(Node<T>* &headPtr);

	template<typename T>
	// Precondition: prevPtr points to Node just before insertion point
	// Postcondition: A new Node with data=info has been inserted into the list after prevPtr
	void insert(Node<T>* prevPtr, const T &info);

	template<typename T>
	// Precondition: prevPtr points to Node just before Node to remove
	// Postcondition: The Node after prevPtr has been removed from the list 
	void remove(Node<T>* prevPtr);

	template<typename T>
	// Precondition: sourcePtr is the head pointer of a linked list.
	// Postcondition: A pointer to a deep copy of the linked list is returned. The original list is
	// unaltered.
	Node<T>* copy(Node<T>* sourcePtr);

	template<typename T>
	void headInsert(Node<T>*& headPtr, const T& data)
	{
		headPtr = new Node<T>(data, headPtr);
	}

	template<typename T>
	void headRemove(Node<T>*& headPtr)
	{
				
		if (headPtr != nullptr)
		{
			Node<T>* tmp = headPtr;
			headPtr = headPtr->next;
			delete tmp;
		}

		else
		{
			std::cout << "The list is empty. There is nothing to remove" << std::endl;
			return;
			//assert(headPtr==nullptr);
			
		}
	}

	template<typename T>
	void insert(Node<T>* prevPtr, const T & info)
	{
		
		if (prevPtr != nullptr)
		{
			Node<T>* tmp = prevPtr->next;
			prevPtr->next = new Node<T>(info);
			prevPtr->next->next = tmp;
			tmp = nullptr;
		}
		
		/*else
		{
			prevPtr = new Node<T>(info,nullptr);
		}*/
	}

	template<typename T>
	void remove(Node<T>* prevPtr)
	{
		if (prevPtr != nullptr)
		{
			Node<T>* tmp = prevPtr->next;
			prevPtr->next = prevPtr->next->next;
			delete tmp;
		}

		else
		{
			std::cout << "The list is empty. There is nothing to remove" << std::endl;
			return;
			//assert(headPtr==nullptr);
		}
	}

	template<typename T>
	Node<T>* copy(Node<T>* sourcePtr)
	{
		// Handle empty source
		if (source == nullptr) return nullptr;

		Node<T>* copyHead = nullptr;	// Head of the copy

		// Create head node for list copy
		headInsert(copyHead, source->info);

		// Keep track of copy's tail
		Node<T>* tail = tail = copyHead;

		// Copy the rest of the nodes, to the tail of list copy.
		for (source = source->next; source != nullptr; tail = tail->next, source = source->next)
		{
			insert(tail, source->info);
		}

		return copyHead;
		/*if (sourcePtr != nullptr)
		{
			Node<T>* tmp = sourcePtr->next;
			sourcePtr->next = new Node<T>(tmp->info);
			Node<T>* tmp2 = sourcePtr->next;

			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
				tmp2->next = new Node<T>(tmp->info);
				tmp2 = tmp2->next;
			}
			return sourcePtr;
		}
		else
			return nullptr;*/
	}
}

