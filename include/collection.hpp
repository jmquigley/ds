#pragma once

#include <memory>

#include "comparator.hpp"
#include "node.hpp"
#include "property.hpp"
#include "stdlib.h"

namespace ds {
template<typename T>
class Collection {
	PROPERTY_SCOPED(first, First, std::shared_ptr<Node<T>>, protected:);
	PROPERTY_SCOPED(last, Last, std::shared_ptr<Node<T>>, protected:);
	PROPERTY_SCOPED(length, Length, size_t, protected:);
	PROPERTY_SCOPED(root, Root, std::shared_ptr<Node<T>>, protected:);

protected:

	Comparator<T> comparator;
	Node<T> nil;

public:

	Collection() : first(nullptr), last(nullptr), length(0), root(nullptr) {}

	Collection(Comparator<T> comparator) : Collection() {
		this->comparator = comparator;
	}

	~Collection() {}

	virtual void clear() = 0;
	virtual std::string str() const = 0;
};
}  // namespace ds
