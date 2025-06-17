/**
 * @brief the base class for all collection object in the library.
 *
 * An abstract class that defines the basic structure of all collection
 * classes
 */
#pragma once

#include <memory>

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
	PROPERTY_SCOPED(front, Front, std::shared_ptr<Node<T>>, protected:);
	/**
	 * @brief Pointer to the last/back element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(back, Back, std::shared_ptr<Node<T>>, protected:);
	/**
	 * @brief The number of elements currently in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(size, Size, size_t, protected:);
	/**
	 * @brief Pointer to the root element of tree-like collections.
	 * @protected
	 */
	PROPERTY_SCOPED(root, Root, std::shared_ptr<Node<T>>, protected:);

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
	Collection() : front(nullptr), back(nullptr), size(0), root(nullptr) {}

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
	 * @brief Clears all elements from the collection, making it empty.
	 * @pure
	 */
	virtual void clear() = 0;

	/**
	 * @brief returns a JSON representation of the given collection.
	 * @pure
	 */
	virtual std::string json() const = 0;

	/**
	 * @brief Returns a string representation of the collection's contents.
	 * @return std::string A string describing the collection.
	 * @pure
	 */
	virtual std::string str() const = 0;
};
}  // namespace ds
