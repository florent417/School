#pragma once
#include "Node.h"
#include "LinkedLists.h"

using namespace LinkedList;

template <typename T>
class Queue
{
public:
	Queue();
	void push(const T &data);
	void pop();
	T front() const;
	bool isEmpty() const;

private:
	LinkedList::Node<T>* frontQueue;
	LinkedList::Node<T>* backQueue;
};

template <typename T>
Queue<T>::Queue()
	: frontQueue(nullptr), backQueue(nullptr)
{
}

template<typename T>
void Queue<T>::push(const T &data)
{
	if (backQueue == nullptr || frontQueue == nullptr)
	{
		headInsert(backQueue, data);
		frontQueue = backQueue;
	}

	else
	{
		insert(backQueue, data);
		backQueue = backQueue->next;
	}
}

template<typename T>
void Queue<T>::pop()
{
	if (frontQueue == nullptr)
	{
	}
	else
		headRemove(frontQueue);
}

template<typename T>
T Queue<T>::front() const
{
	if(!isEmpty())
		return frontQueue->info;

	throw std::exception("front called on empty FIFO");
}


template<typename T>
bool Queue<T>::isEmpty() const
{
	return frontQueue == nullptr;
}