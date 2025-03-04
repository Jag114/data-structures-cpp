#pragma once

#include <initializer_list>
#include <iostream>

template <typename T>
class List {
private:
	class Node {
	private:
		T value = 0;
		std::shared_ptr<Node> next = nullptr;
	public:
		Node() = delete;

		Node(T value, Node nextNode) : value(value) {
			next = std::make_shared<Node>(1);
		};

		Node(T value) : value(value) {};

		Node (const Node& other) {
			value = other.value;
			//next = other.next;
		}

		T GetValue() {
			return value;
		}

		void SetValue(T newValue) {
			value = newValue;
		};
	};

	Node head = NULL;

public:
	List() = default;

	List(T value);
	
	List(std::initializer_list<T> list);

	void PushBack(T value);

	void Display();

	List<T>& operator=(const List& other);
};


template <typename T>
List<T>::List(T value) {
	head = Node(value);
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
	Node currNode{ head };
	std::cout << currNode.GetValue() << "\n";
}


