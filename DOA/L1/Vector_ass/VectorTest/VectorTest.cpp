#include "pch.h"
#include "../Vector_ass/Vector.h"

/*
TEST(Vector, Get_getInvalidIndex_returnFalse) {
	Vector uut;

	int result = uut.get(12);

	EXPECT_TRUE(result);
}*/

TEST(Vector, HowMany_HowMany0_returns10) {
	Vector uut;

	int result = uut.howMany(0);

	ASSERT_EQ(10, result);
}