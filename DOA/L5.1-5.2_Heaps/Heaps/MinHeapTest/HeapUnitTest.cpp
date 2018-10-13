#include "pch.h"
#include "../Heaps/MinHeap_201409781FlorentAvdijaj.h"

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

class MinHeapUnitTest : public ::testing::Test
{
protected:

	void SetUp()
	{
	}

	void TearDown()
	{
	}

	MinHeap<int> uut;
};


TEST_F(MinHeapUnitTest, Ctor_VanillaHeap_HeapIsEmpty)
{
	ASSERT_TRUE(uut.isEmpty());
}


TEST_F(MinHeapUnitTest, Ctor_OneElementInserted_HeapIsNotEmpty)
{
	uut.insert(2);
	ASSERT_FALSE(uut.isEmpty());
}



TEST_F(MinHeapUnitTest, Peek_OneElementInserted_CorrectElementInFront)
{
	uut.insert(2);
	ASSERT_EQ(2, uut.peek());
}

TEST_F(MinHeapUnitTest, Peek_OneElementInsertedTwoPeeks_CorrectElementInFront)
{
	uut.insert(2);
	uut.peek();
	ASSERT_EQ(2, uut.peek());
}


TEST_F(MinHeapUnitTest, Insert_TwoElementInserted_CorrectElementInFront)
{
	uut.insert(2);
	uut.insert(3);
	ASSERT_EQ(2, uut.peek());
}

TEST_F(MinHeapUnitTest, Insert_SameElementInsertedTwice_CorrectElementInFront)
{
	uut.insert(2);
	uut.insert(2);
	ASSERT_EQ(2, uut.peek());
}

TEST_F(MinHeapUnitTest, Insert_TwoElementInsertedReverseOrder_CorrectElementInFront)
{
	uut.insert(3);
	uut.insert(2);
	ASSERT_EQ(2, uut.peek());
}

TEST_F(MinHeapUnitTest, Remove_OneElementInserted_HeapIsEmpty)
{
	uut.insert(2);
	uut.remove();
	ASSERT_TRUE(uut.isEmpty());
}


TEST_F(MinHeapUnitTest, Remove_TwoElementsInsertedOneRemoved_HeapIsNotEmpty)
{
	uut.insert(2);
	uut.insert(3);
	uut.remove();
	ASSERT_FALSE(uut.isEmpty());
}

TEST_F(MinHeapUnitTest, Remove_TwoElementsInsertedTwoRemoved_HeapIsEmpty)
{
	uut.insert(2);
	uut.insert(3);
	uut.remove();
	uut.remove();
	ASSERT_TRUE(uut.isEmpty());
}

TEST_F(MinHeapUnitTest, Remove_SameElementInsertedTwiceThenRemovedOnce_HeapIsNotEmpty)
{
	uut.insert(2);
	uut.insert(2);
	uut.remove();
	ASSERT_FALSE(uut.isEmpty());
}


TEST_F(MinHeapUnitTest, Remove_SameElementInsertedTwiceThenBothRemoved_HeapIsEmpty)
{
	uut.insert(2);
	uut.insert(2);
	uut.remove();
	uut.remove();
	ASSERT_TRUE(uut.isEmpty());
}

TEST_F(MinHeapUnitTest, Remove_SameElementInsertedOneRemoved_CorrectElementInFront)
{
	uut.insert(2);
	uut.insert(2);
	uut.remove();
	ASSERT_EQ(2, uut.peek());
}

TEST_F(MinHeapUnitTest, Remove_TwoElementsInsertedOneRemoved_CorrectElementInFront)
{
	uut.insert(2);
	uut.insert(3);
	uut.remove();
	ASSERT_EQ(3, uut.peek());
}

TEST_F(MinHeapUnitTest, Insert_FourElementsInsertedUnOrdered_CorrectElementInFront)
{
	uut.insert(5);
	uut.insert(15);
	uut.insert(3);
	uut.insert(5);
	ASSERT_EQ(3, uut.peek());
}

TEST_F(MinHeapUnitTest, Insert_FourElementsInsertedOneRemoved_CorrectElementInFront)
{
	uut.insert(5);
	uut.insert(15);
	uut.insert(4);
	uut.insert(10);
	uut.remove();
	ASSERT_EQ(5, uut.peek());
}