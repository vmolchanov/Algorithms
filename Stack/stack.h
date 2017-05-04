#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <cstdlib>

template<typename T>
class Stack {

public:
	Stack(size_t size = 10) : size(0), capacity(size) {
		stack = (T*)malloc(size * sizeof(T));
	}


	~Stack() {
		free(stack);
	}


	size_t getSize() {
		return size;
	}


	size_t getCapacity() {
		return capacity;
	}


	bool isEmpty() {
		return !size;
	}


	void push(T a) {
		size++;

		if (capacity < size) {
			this->stack = (T*)realloc(this->stack, size * sizeof(T));
			capacity = size;
		}

		stack[size - 1] = a;
	}
	

	T pop() {
		size--;
		return stack[size];
	}

private:
	T *stack;
	size_t size;
	size_t capacity;
};

#endif
