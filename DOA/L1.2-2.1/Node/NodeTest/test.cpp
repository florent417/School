#include "pch.h"
#include "../Node/Node.h"
#include <gtest/gtest.h>

using namespace LinkedList;

TEST(NodeTest, Ctor_NoArgs_ValueIsDefault)
{
	Node<int>* uut = new Node<int>();
	int _info = uut->info;
	ASSERT_EQ(_info, 0);
}

TEST(NodeTest, Ctor_NoArgs_NextIsnullptr)
{
	Node<int>* uut = new Node<int>();
	Node<int>* _nullptr = nullptr;
	ASSERT_EQ(uut->next, _nullptr);
}

TEST(NodeTest, Ctor_InfoArg_ValueIs2)
{
	Node<int>* uut = new Node<int>(2);
	int _info = uut->info;
	ASSERT_EQ(_info, 2);
}

TEST(NodeTest, Ctor_NextArg_NextIsCorrect)
{
	Node<int>* next = new Node<int>();
	Node<int>* uut = new Node<int>(0, next);

	ASSERT_EQ(uut->next, next);
}

TEST(NodeTest, SetInfo_SetInfo_InfoIsCorrect)
{
	Node<int>* uut = new Node<int>(0);
	uut->info = 4;

	ASSERT_EQ(uut->info, 4);
}