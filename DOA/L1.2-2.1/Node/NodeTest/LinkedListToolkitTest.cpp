#include "pch.h"
#include "../Node/Node.h"
#include <gtest/gtest.h>
#include "../Node/LLToolkit_handout.h"

using namespace LinkedList;

//================================================
// Test fixture for LLToolkit
//================================================
class LLToolkitTest : public testing::Test //Hvad betyder det her?
{
protected:
	LLToolkitTest()
	{
		valToInsert = 2;// In some tests, explicitly declared value to insert
						//	pointer is necessary due to strict typing in templates

		emptyList = nullptr;
		singleElementList = new Node<int>(valToInsert);

		n3 = new Node<int>(3);
		n2 = new Node<int>(2, n3);
		n1 = new Node<int>(1, n2);
	}

	~LLToolkitTest()
	{
	}


	// Test members
	Node<int>* emptyList;
	Node<int>* singleElementList;
	int valToInsert;


	Node<int>* n1;
	Node<int>* n2;
	Node<int>* n3;
};

TEST_F(LLToolkitTest, HeadInsert_EmptyList_HeadValueIsCorrect)
{
	Node<int>* head = nullptr;

	headInsert(head, valToInsert);
	EXPECT_EQ(head->info, valToInsert);
}

TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadValueIsCorrect)
{
	headInsert(n1, valToInsert);
	EXPECT_EQ(n1->info, valToInsert);
}


TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadNextCorrect)
{
	Node<int>* oldN1 = n1;
	headInsert(n1, valToInsert);
	EXPECT_EQ(n1->next, oldN1);
}

TEST_F(LLToolkitTest, HeadRemove_EmptyList_NotPossible)
{
	headRemove(emptyList);
}

TEST_F(LLToolkitTest, HeadRemove_NonEmptyList_HeadIsNull)
{
	headRemove(singleElementList);
	EXPECT_EQ(singleElementList, nullptr);
}

TEST_F(LLToolkitTest, HeadRemove_NonEmptyList_HeadIsNextNode)
{
	headRemove(n1);
	EXPECT_EQ(n1, n2);
}

TEST_F(LLToolkitTest, Insert_NonEmptyList_InsertedValueCorrect)
{
	insert(singleElementList, valToInsert);
	EXPECT_EQ(singleElementList->info, valToInsert);
}

TEST_F(LLToolkitTest, Remove_NonEmptyList_InsertedValueCorrect)
{
	remove(n1);
	EXPECT_EQ(n1->next, n3);
}

/*
TEST_F(LLToolkitTest, Insert_EmptyList_InsertedNextIsNull)
{
	insert(emptyList, valToInsert);
	EXPECT_EQ(emptyList->info, valToInsert);
}*/

/*
TEST_F(LLToolkitTest, Copy_NonEmptyList_ValueIsCorrect)
{
	Node<int>* oldN1 = n1;
	copy(oldN1);
	EXPECT_NE(oldN1->next->next, n1->next->next);
}*/
/*
TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadNextCorrect)
{
	Node<int>* copyN1 = copy(n1);
	EXPECT_EQ(n2->info, copyN1->next->info );
}*/

