/**
 * @brief the base class for all collection object in the library.
 *
 * An abstract class that defines the basic structure of all collection
 * classes
 */
#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "comparator.hpp"
#include "node.hpp"
#include "property.hpp"
#include "stdlib.h"

/**
 * @file collection.hpp
 * @brief Defines the base abstract class for various data collections.
 */

namespace ds {
/**
 * @brief Namespace for data structures.
 */
template<typename T>
class Collection {
	/**
	 * @brief Pointer to the first/front element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(_front, Front, std::weak_ptr<Node<T>>, protected:);
	/**
	 * @brief Pointer to the last/back element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(_back, Back, std::weak_ptr<Node<T>>, protected:);
	/**
	 * @brief The number of elements currently in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(_size, Size, size_t, protected:);
	/**
	 * @brief Pointer to the root element of tree-like collections.
	 * @protected
	 */
	PROPERTY_SCOPED(_root, Root, std::shared_ptr<Node<T>>, protected:);

protected:

	/**
	 * @brief A comparator object used for ordering elements within the collection.
	 *
	 * A default comparison object that is available to all classes that are part
	 * of the collection.
	 */
	Comparator<T> comparator;
	/**
	 * @brief A sentinel node often used in tree-based or linked-list structures.
	 *
	 * An empty node that can be used for comparison as a NIL value.
	 */
	Node<T> nil;

public:

	/**
	 * @brief Default constructor for Collection.
	 * Initializes pointers to nullptr and length to 0.
	 */
	Collection() : _front(), _back(), _size(0), _root(nullptr) {}

	/**
	 * @brief Constructor for Collection that takes a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	Collection(Comparator<T> comparator) : Collection() {
		this->comparator = comparator;
	}

	/**
	 * @brief Virtual destructor for Collection.
	 * Ensures proper cleanup of derived classes.
	 */
	virtual ~Collection() {}

	/**
	 * @brief Checks if the contents of two given collections are equal
	 * @param col (`Collection &`) the collection to compare against
	 * @return true if both collections have the same values, otherwise false
	 */
	bool operator==(const Collection<T> &col) const {
		if (this->_size != col.size()) {
			return false;
		}

		std::shared_ptr<Node<T>> r1 = this->_root;
		std::shared_ptr<Node<T>> r2 = col.getRoot();

		while (r1 && r2) {
			if (this->comparator(r1->getData(), r2->getData()) != 0) {
				return false;
			}

			r1 = r1->getRight();
			r2 = r2->getRight();
		}

		return true;
	}

	/**
	 * @brief Checks if the contents of two given collections are not equal
	 * @param col (`Collection &`) the list to compare against
	 * @return false if both lists have the same values, otherwise true
	 */
	bool operator!=(const Collection<T> &col) const {
		return !operator==(col);
	}

	/**
	 * @brief Operator to clear the buffer.
	 *
	 * This is a convenience wrapper for the `clear` function, resetting the
	 * container's size to zero.
	 *
	 * @return A reference to the current object (`*this`).
	 */
	Collection<T> &operator~() {
		this->clear();
		return *this;
	}

	/**
	 * @brief retrieves the element at the end of the collection
	 * @return a `T` data element
	 * @throws std::bad_weak_ptr if the requested back pointer is not available
	 */
	T back() {
		return this->_back.lock()->getData();
	}

	/**
	 * @brief Clears all elements from the collection, making it empty.
	 * @pure
	 */
	virtual void clear() = 0;

	/**
	 * @brief Checks a container for the existence of the given T element
	 * @return true if found in the container, otherwise false
	 */
	virtual bool contains(T data) = 0;

	/**
	 * @brief Check if the collection is empty
	 * @return true if the colleciton is empty, otherwise false
	 */
	bool empty() {
		return this->_size == 0;
	}

	/**
	 * @brief retrieves the element at the front of the collection
	 * @return a `T` data element
	 */
	T front() {
		return this->_front.lock()->getData();
	}

	/**
	 * @brief returns a JSON representation of the given collection.
	 * @pure
	 */
	virtual std::string json() const = 0;

	/**
	 * @brief returns the size of the collection class
	 */
	size_t size() const {
		return this->_size;
	}

	/**
	 * @brief Returns a string representation of the collection's contents.
	 * @return std::string A string describing the collection.
	 * @pure
	 */
	virtual std::string str() const = 0;
};
}  // namespace ds
