#include "pch.h"
#include <gtest/gtest.h>
#include "..\OAHashMap\OAHashMap.h"


const int TABLE_SIZE = 4 * 20 + 3;
int hash(int key) { return 0;}

//================================================
// Test fixture for OAHashMap
//================================================
class OAHashMapTest : public ::testing::Test
{
protected:
	OAHashMapTest() : index(0), size(TABLE_SIZE), searchResult(-1)
	{
		map = new OAHashMap<int, int>(size, hash);
	}

	~OAHashMapTest()
	{
		delete map;
	}


	OAHashMap<int, int>* map;
	size_t index;
	int size;
	int searchResult;
};

TEST_F(OAHashMapTest, CtorAndGetLoadFactor_LoadFactorIsZero)
{
	EXPECT_EQ(0, map->getLoadFactor());
}


TEST_F(OAHashMapTest, Search_EmptyMap_SearchReturnsFalse)
{
	EXPECT_FALSE(map->search(1, searchResult));
}


TEST_F(OAHashMapTest, Search_OneInserted_SearchReturnsTrue)
{
	map->insert(1,1);
	EXPECT_TRUE(map->search(1, searchResult));
}

TEST_F(OAHashMapTest, Search_SeveralElementsInserted_SearchReturnsTrue)
{
	map->insert(1,1);
	map->insert(2,2);
	map->insert(3,3);
	map->insert(4,4);
	map->insert(5,5);
	EXPECT_TRUE(map->search(3, searchResult));
	EXPECT_EQ(3, searchResult);
}

TEST_F(OAHashMapTest, InsertAndGetLoadFactor_OneInserted_LoadFactorIsCorrect)
{
	map->insert(1,1);
	EXPECT_DOUBLE_EQ(static_cast<double>(1) / size, map->getLoadFactor());
}


TEST_F(OAHashMapTest, InsertAndGetLoadFactor_OneInsertedTwice_LoadFactorIsCorrect)
{
	map->insert(1, 1);
	map->insert(1, 1);
	EXPECT_DOUBLE_EQ(static_cast<double>(1) / size, map->getLoadFactor());
}

TEST_F(OAHashMapTest, InsertAndGetLoadFactor_OneTwoInserted_LoadFactorIsCorrect)
{
	map->insert(1, 1);
	map->insert(2, 2);
	EXPECT_DOUBLE_EQ(static_cast<double>(2) / size, map->getLoadFactor());
}


TEST_F(OAHashMapTest, InsertAndGetLoadFactor_FillMap_LoadFactorCorrect)
{
	for (int i = 0; i < size; i++)	map->insert(i, i);

	EXPECT_DOUBLE_EQ(1.0, map->getLoadFactor());
}

TEST_F(OAHashMapTest, Insert_InsertIntoFullMap_ExceptionThrown)
{
	EXPECT_THROW({
		for (int i = 0; i < size; i++)	map->insert(i, i);
			map->insert(size + 1, size+1);
		}, OAHashMapException);
}

TEST_F(OAHashMapTest, Insert_RemoveFromFullMapThenInsert_NoExceptionThrown)
{
	EXPECT_NO_THROW({
		for (int i = 0; i < size; i++)	map->insert(i, i);
	map->remove(0);
	map->insert(size + 1, size+1);
		});
}


TEST_F(OAHashMapTest, Remove_EmptyMap_NoError)
{
	EXPECT_NO_THROW(map->remove(1));
}


TEST_F(OAHashMapTest, Remove_ExistingElement_ElementRemoved)
{
	map->insert(1, 1);
	map->remove(1);

	EXPECT_FALSE(map->search(1, searchResult));
	EXPECT_EQ(-1, searchResult);
}


TEST_F(OAHashMapTest, Remove_ExistingElement_OtherElementsUntouched)
{
	map->insert(1,1);
	map->remove(1);
	map->remove(2);
	EXPECT_FALSE(map->search(2, searchResult));
	EXPECT_EQ(-1, searchResult);
}


TEST_F(OAHashMapTest, Remove_NonExistingElement_OtherElementsUntouched)
{
	map->insert(1,1);
	map->remove(2);
	EXPECT_TRUE(map->search(1, searchResult));
	EXPECT_EQ(1, searchResult);
}

