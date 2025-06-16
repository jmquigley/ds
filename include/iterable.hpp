/**
 * @brief Defines the interface that is used by all iterable data structures.
 */

#pragma once

#include <limits>

#include "match.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @enum Position
 * @brief Defines standard positions for insertion operations.
 *
 * This enum provides constants for common insertion positions
 * that can be used across different data structures.
 *
 * @var Position::FRONT
 * @brief Represents the front/beginning position (value 0).
 *
 * @var Position::BACK
 * @brief Represents the back/end position (value -1).
 */
enum class Position : size_t { FRONT = 0, BACK = std::numeric_limits<std::size_t>::max() };

/**
 * @class Iterable
 * @brief An interface definition for all iterable collections.
 *
 * @tparam T The type of data stored within the collection.
 */
template<typename T>
class Iterable {
public:

	/**
	 * @brief Find function for iterable collection classes.
	 * @param data The element to search for in the collection
	 * @return Match<T> A match object indicating whether the element was found
	 * @pure
	 */
	virtual Match<T> find(T data) = 0;

	/**
	 * @brief Insert the given data into a collection at back of the collection
	 * @param data The element to insert
	 * @pure
	 */
	virtual void insert(T data) = 0;

	/**
	 * @brief Removes the given data element by its index location
	 * @param index (`size_t`) the location within the collection to remove
	 * @param tnode (`std::shared_ptr<Node<T>>`) a convenience cache node from a search to
	 * help short circuit a lookup for deletion that has already occurred.
	 */
	virtual void removeAt(size_t index, std::shared_ptr<Node<T>> tnode = nullptr) = 0;

	/**
	 * @brief Removes the first instance of the given value from the list.
	 * @param value (`T`) a data value to find and remove from the list
	 */
	virtual void removeValue(T value) = 0;
};
}  // namespace ds
