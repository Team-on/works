#pragma once

template <typename T>
class StackArr {
	static const short int MAX_SIZE = 256;
	T stack[MAX_SIZE];
	int head;

public:
	StackArr() {
		head = -1;
	}
	bool isEmpty() const {
		return head == -1;
	}
	bool isFull() const {
		return head == MAX_SIZE - 1;
	}

	void push(T p) {
		if (!isFull())
			stack[++head] = p;
	}
	T pop() {
		if (!isEmpty())
			return stack[head--];
		return 0;
	}
};