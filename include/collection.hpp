#pragma once

#include "comparator.hpp"
#include "node.hpp"
#include "property.hpp"
#include "stdlib.h"

template<typename T>
class Collection {
	PROPERTY(first, First, Node<T> *);
	PROPERTY(last, Last, Node<T> *);
	PROPERTY(length, Length, size_t);
	PROPERTY_READONLY(root, Root, Node<T> *);

protected:

	Comparator<T> comparator;
	Node<T> nil;

public:

	Collection() : first(nullptr), last(nullptr), length(0), root(nullptr) {}

	Collection(Comparator<T> comparator) : Collection() {
		this->comparator = comparator;
	}

	~Collection() {}
};
