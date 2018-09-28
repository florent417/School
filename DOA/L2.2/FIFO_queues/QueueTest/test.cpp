#include "pch.h"
#include "gtest/gtest.h"
#include "../FIFO_queues/Queue.h"

class QueueUnitTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		uut = new Queue<int>;
	}

	void TearDown() override
	{
		delete uut;
	}

	Queue<int>* uut;
};

TEST(Queue, Push_EmptyQueue_Succes) {
	
	Queue<int>* uut = new Queue<int>;

	uut->push(1);
	EXPECT_EQ(uut->front(), 1);
}

TEST_F(QueueUnitTest, Ctor_Ctor_QueueEmpty)
{
	EXPECT_TRUE(uut->isEmpty());
}

TEST_F(QueueUnitTest, Ctor_Push_QueueNotEmpty)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	EXPECT_FALSE(uut->isEmpty());
}

TEST_F(QueueUnitTest, PushPop_PushPop_QueueEmpty)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	uut->pop();
	EXPECT_TRUE(uut->isEmpty());
}

TEST_F(QueueUnitTest, PushPop_PushTimes2Pop_QueueNotEmpty)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	uut->push(1);
	uut->pop();
	EXPECT_FALSE(uut->isEmpty());
}

TEST_F(QueueUnitTest, Front_EmptyQueue_ExceptionThrown)
{
	Queue<int>* uut = new Queue<int>;
	EXPECT_THROW(
		{
			uut->front();
		}, std::exception);
}


TEST_F(QueueUnitTest, Front_PushTimes3_FrontIsCorrect)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	uut->push(2);
	uut->push(3);

	EXPECT_EQ(uut->front(), 1);
}

TEST_F(QueueUnitTest, Front_PushTimes3Frontx2_FrontIsCorrect)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	uut->push(2);
	uut->push(3);
	uut->front();

	EXPECT_EQ(uut->front(), 1);
}

TEST_F(QueueUnitTest, Ctor_PushTimes3Pop_FrontIsCorrect)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	uut->push(2);
	uut->push(3);
	uut->pop();

	EXPECT_EQ(uut->front(), 2);
}



TEST_F(QueueUnitTest, Ctor_PushTimes3PopTimes2_FrontIsCorrect)
{
	Queue<int>* uut = new Queue<int>;
	uut->push(1);
	uut->push(2);
	uut->push(3);
	uut->pop();
	uut->pop();

	EXPECT_EQ(uut->front(), 3);
}