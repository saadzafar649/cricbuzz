#include "Includes.h"
#pragma once
#ifndef ARRAY_H
#define ARRAY_H

template<class dataType>
class Array {
	dataType* arr;
	dataType* temp;
	int capacity;
public:
	int size;
	Array(int capacity = 2, int size = 0) :capacity(capacity), size(size) {
		temp = nullptr;
		arr = new dataType[capacity];
	}
	int capacityleft() {
		return capacity - size;
	}
	dataType* incCapacity(int num = 1) {
		capacity += num;
		temp = new dataType[capacity];
		//temp[0] = dataType();
		for (int i = 0; i < size; i++) {
			temp[i] = arr[i];
		}
		delete[]arr;
		arr = temp;
		return temp;
	}
	void append(dataType data) {
		if (size >= capacity) {
			incCapacity(2);
		}
		arr[size] = data;
		size++;
	}
	void pop() {
		size--;
	}
	void remove(int index) {
		arr[index] = arr[size - 1];
		size--;
	}
	dataType& getlast() {
		return arr[size - 1];
	}
	dataType&operator[](int num) {
		try {
			if (num < size && num > 0)
				return arr[num];
			throw num;
		}
		catch (int num) {
			return arr[0];
		}
	}
	~Array() {
		delete[]arr;
		arr = NULL;
	}
};

#endif // !ARRAY_H