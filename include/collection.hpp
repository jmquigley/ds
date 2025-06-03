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
	 * @brief Pointer to the first element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(first, First, std::shared_ptr<Node<T>>, protected:);
	/**
	 * @brief Pointer to the last element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(last, Last, std::shared_ptr<Node<T>>, protected:);
	/**
	 * @brief The number of elements currently in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(length, Length, size_t, protected:);
	/**
	 * @brief Pointer to the root element of tree-like collections.
	 * @protected
	 */
	PROPERTY_SCOPED(root, Root, std::shared_ptr<Node<T>>, protected:);

protected:

	/**
	 * @brief A comparator object used for ordering elements within the collection.
	 */
	Comparator<T> comparator;
	/**
	 * @brief A sentinel node often used in tree-based or linked-list structures.
	 */
	Node<T> nil;

public:

	/**
	 * @brief Default constructor for Collection.
	 * Initializes pointers to nullptr and length to 0.
	 */
	Collection() : first(nullptr), last(nullptr), length(0), root(nullptr) {}

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
	 * @brief Clears all elements from the collection, making it empty.
	 * @pure
	 */
	virtual void clear() = 0;
	/**
	 * @brief Returns a string representation of the collection's contents.
	 * @return std::string A string describing the collection.
	 * @pure
	 */
	virtual std::string str() const = 0;
};
}  // namespace ds
