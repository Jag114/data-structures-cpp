#include "Array.h"
#include "List.h"
#include "BinaryTree.h"
#include "HashMap.h"
#include "Map.h"
#include "Queue.h"
#include "Stack.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

int main()
{
	std::vector<int> v = { 1,2,3 };
	std::vector<int>::iterator;
	Array<int> arr1 = { 1,2,3 };
	std::cout << "end - begin + 2 " << *(arr1.Begin() + (arr1.End() - 2)) << std::endl;
	std::cout << "* end - 2 " << *(arr1.End() - 2) << std::endl;
	std::cout << "* Begin " << *(arr1.Begin()) << std::endl;
	std::sort(v.begin(), v.end(), [](int a, int b) {return a > b; });
	/*
	Array<int> arr1 = { 1,2,3,7,3,5 };
	Array<int> arr2 = { 10,11,12 };

	std::cout << "Display with iterator" << std::endl;
	Array<int>::iterator it = arr1.Begin();
	for (auto it = arr1.Begin(); it != arr1.End(); ++it) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
	std::cout << "Add two arrays" << std::endl;
	arr1 = arr1 + arr2;
	std::cout << "Display" << std::endl;
	arr1.Display();
	std::cout << "Display capacity" << std::endl;
	std::cout << arr1.GetCapacity() << std::endl;
	std::cout << "Reserve 10" << std::endl;
	arr1.Reserve(10);
	std::cout << "Display capacity" << std::endl;
	std::cout << arr1.GetCapacity() << std::endl;

	std::vector<int> v;
	Array<int> a;

	exit(0);
	*/
}