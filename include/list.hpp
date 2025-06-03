/**
 * @file list.hpp
 * @brief Defines a doubly linked list data structure collection.
 */

#pragma once

#include <vector>

#include "collection.hpp"
#include "iterable.hpp"
#include "property.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class List
 * @brief A generic doubly linked list class.
 *
 * @tparam T The type of data stored within the list.
 */
template<typename T>
class List : public Collection<T>, public Iterable<T> {

public:
	List() : Collection<T>() {}

	List(Comparator<T> comparator) : Collection<T>(comparator) {}

	~List() {}

	T at(size_t pos) {
		// TODO: add at() to List
	}

	std::vector<T> array(void) {
		// TODO: add array() to List
	}

	virtual void clear() override {
		// TODO: add clear() to List
	}

	virtual Node<T> find(T data) override {
		// TODO: add find() to List
	}

	virtual void insert(T data) override {
		// TODO: add insert() to List
	}

	virtual void remove(T data) override {
		// TODO: add remove() to List
	}

	std::vector<T> reverse() {
		// TODO: add reverse() to List
	}

	virtual std::string str() override {
		// TODO: add str() to List
	}
};
}  // namespace ds
