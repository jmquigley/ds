#pragma once

#include <ds/SortedList.hpp>
#include <iostream>

namespace ds {

/**
 * @class OrderedSet
 * @brief A collection that contains no duplicate elements, maintaining values
 * in sorted order.
 *
 * OrderedSet extends SortedList to enforce uniqueness of elements. It
 * automatically arranges elements according to their natural ordering (using a
 * comparator) and prevents duplicate entries from being inserted. Unlike a
 * standard set, OrderedSet maintains insertion order for equivalent elements.
 *
 * @tparam T The type of elements stored in the ordered set
 */
template<typename T>
class OrderedSet : public SortedList<T> {
public:

	/**
	 * @brief Default constructor
	 *
	 * Creates an empty OrderedSet with the default comparator for type T.
	 */
	OrderedSet() : SortedList<T>() {}

	/**
	 * @brief Copy constructor
	 *
	 * Creates a new OrderedSet as a copy of an existing one.
	 *
	 * @param set (`OrderedSet<T>`) The ordered set to copy
	 */
	OrderedSet(const OrderedSet<T> &set) : SortedList<T>(set) {}

	/**
	 * @brief Move constructor
	 * @param set (`OrderedSet<T> &&`) an rvalue reference to a ordered set to
	 * move
	 */
	OrderedSet(OrderedSet<T> &&set) : SortedList<T>(std::move(set)) {}

	/**
	 * @brief Initializer list constructor
	 *
	 * Creates an OrderedSet containing the elements from the initializer list.
	 * Duplicate elements in the initializer list will be ignored.
	 *
	 * @param il (`std::initializer_list<T>`) A list of values to initialize the
	 * set
	 */
	OrderedSet(const std::initializer_list<T> &il) : SortedList<T>() {
		for (const auto &it: il) {
			this->insert(it);
		}
	}

	/**
	 * @brief Assignment operator
	 *
	 * Assigns the contents of another OrderedSet to this one.
	 *
	 * @param other (`OrderedSet<T>`) The ordered set to copy from
	 * @return Reference to this OrderedSet after assignment
	 */
	OrderedSet<T> &operator=(const OrderedSet<T> &other) {
		SortedList<T>::operator=(other);
		return *this;
	}

	/**
	 * @brief Assignment operator for an initializer list
	 *
	 * Assigns the contents of an intializer list to the set
	 *
	 * @param il (`std::initializer_list<T>`) a reference to an initalizer list
	 * @return Reference to this OrderedSet after assignment
	 */
	OrderedSet<T> &operator=(const std::initializer_list<T> &il) {
		SortedList<T>::operator=(il);
		return *this;
	}

	/**
	 * @brief Inserts an element into the set
	 *
	 * Adds the element to the set only if it is not already present.
	 * Elements are inserted in sorted order according to the set's comparator.
	 *
	 * @param data The element to insert
	 */
	virtual void insert(T data) override {
		if (!this->contains(data)) {
			SortedList<T>::insert(data);
		}
	}
};

}  // namespace ds
