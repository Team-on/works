#pragma once

#include <iostream>
using namespace std;

template <typename T>
class Queue {
	static const short int MAX_SIZE = 256;
	T stack[MAX_SIZE];
	int head;
	int tail;
	int size;
public:
	Queue() {
		head = tail = -1;
		size = 0;
	}
	bool isEmpty() const {
		return size == 0;
	}
	bool isFull() const {
		return size == MAX_SIZE - 1;
	}

	void push(char p) {
		if (!isFull()) {
			++size;
			stack[++tail] = p;
			if (tail == MAX_SIZE - 1)
				tail = -1;
		}
		else
			cout << "Queue overflow";
	}
	T pop() {
		if (!isEmpty()) {
			--size;
			T rez = stack[++head];
			if (head == MAX_SIZE - 1)
				head = -1;
			return rez;
		}
		cout << "Queue empty";
		return 0;
	}
};

