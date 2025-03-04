#include "pch.h"
#include <algorithm>

#include "List.h"
#include "Array.h"


TEST(ArrayTest, Add) {
	Array<int> arr1 = { 1,3,2,8,7,5 };
	size_t oldSize = arr1.GetLength();
	arr1.Add(1, 5);
	EXPECT_EQ(arr1[1], 5);
	EXPECT_EQ(oldSize + 1, arr1.GetLength());
}

TEST(ArrayTest, Add2) {
	Array<int> arr1 = { 1,3,2,8,7,5 };
	Array<int> arr2 = { 19, 92, 44 };
	Array<int> arr3 = { 1,3,2,19,92,44,8,7,5 };
	arr1.Add(3, arr2);
	arr1.Display();
	for (size_t i = 0; i < arr1.GetLength(); ++i) {
		EXPECT_EQ(arr1[i], arr3[i]);
	}
}

TEST(ArrayTest, Delete) {
	Array<int> arr1 = { 1,3,2,8,7,5 };
	size_t oldSize = arr1.GetLength();
	arr1.Delete(3, 1);
	EXPECT_EQ(arr1[3], 7);
	EXPECT_EQ(oldSize - 1, arr1.GetLength());
}


TEST(ArrayTest, Sort) {
	Array<int> arr1 = { 1,3,2,8,7,5 };
	Array<int> arr2 = { 1,2,3,5,7,8 };

	std::sort(arr1.Begin(), arr1.End(), [] (int a, int b) {return a < b; });

	for (size_t i = 0; i < arr1.GetLength(); ++i) {
		EXPECT_EQ(arr1[i], arr2[i]);
	}
}

TEST(ListTest, first) {
	List<int> l1{ 2 };
	l1.Display();
}