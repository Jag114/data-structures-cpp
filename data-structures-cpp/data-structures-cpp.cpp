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

bool compare(int a, int b) {
	return a > b;
}

int main()
{
	Array<int> arr1 = { 1,2,3,7,3,5 };
	Array<int> arr2 = { 10,11,12 };
	std::cout << "Display" << std::endl;
	arr1.Display();
	std::cout << "Sort" << std::endl;
	arr1.Sort(compare);
	std::cout << "Display" << std::endl;
	arr1.Display();
	std::cout << "Add 5 at index 1" << std::endl;
	arr1.Add(1, 5);
	std::cout << "Display" << std::endl;
	arr1.Display();
	std::cout << "Delete 1 element after index 4" << std::endl;
	arr1.Delete(4, 1);
	std::cout << "Display" << std::endl;
	arr1.Display();
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

}