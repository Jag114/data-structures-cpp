#include "pch.h"
#include "Array.h"
#include <algorithm>

TEST(ArrayTest, Add) {
	Array<int> arr1 = { 1,3,2,8,7,5 };
	size_t oldSize = arr1.GetLength();
	arr1.Add(1, 5);
	EXPECT_EQ(arr1[1], 5);
	EXPECT_EQ(oldSize + 1, arr1.GetLength());
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

	
	
	//std::sort(arr1.Begin(), arr1.End(), [] (int a, int b) {return a > b; });
	Array<int>::iterator it = arr1.Begin();
	void* data = (void*)(&(*it));
	std::qsort(data, arr1.GetLength(), sizeof(int), [](const void* a, const void* b) {
		const int* x = (int*)a;
		const int* y = (int*)b;

		if (*x > *y)
			return 1;
		else if (*x < *y)
			return -1;

		return 0;
	});
	
	for (size_t i = 0; i < arr1.GetLength(); ++i) {
		EXPECT_EQ(arr1[i], arr2[i]);
	}
}