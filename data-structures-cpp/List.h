#pragma once

#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <cstddef>

template <typename T>
class List {
private:
	class Node {
		T value = default;
		std::unique_ptr<Node> next = nullptr;
		
	public:
		Node(T value, Node nextNode) {

		};

		Node(T value) : value(value) {};

		Node() = delete;

		T GetValue() {

		}

		void SetValue(T value) {

		};

		Node GetNext() {

		}

		void SetNext(Node nextNode) {

		}
	};

	Node head;

public:
	List();

	List(std::initializer_list<T> list);

	void PushBack(T value);

	void Display();

	List<T>& operator=(const List& other);
};

template <typename T>
List<T>::List() {

}

template <typename T>
List<T>::List(std::initializer_list<T> list) {
	
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
	
}

template <typename T>
void List<T>::PushBack(T value) {
	
}

template <typename T>
void List<T>::Display() {
	
}


