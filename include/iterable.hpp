/**
 * @file iterable.hpp
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
	 * @brief Insert the given data into a collection at specified position.
	 * @param data The element to insert
	 * @param position The position to insert at (FRONT or BACK, default is BACK)
	 * @throws std::runtime_error If an invalid position is specified
	 * @pure
	 */
	virtual void insert(T data, Position position = Position::BACK) = 0;

	/**
	 * @brief Insert the given data into a collection at specified index.
	 * @param data The element to insert
	 * @param index The index at which to insert the element (default is max size_t, which typically
	 * inserts at the end)
	 * @pure
	 */
	virtual void insert(T data, size_t index = std::numeric_limits<std::size_t>::max()) = 0;

	/**
	 * @brief Removes the given data element from the structure if it exists.
	 * @pure
	 */
	virtual void remove(T data) = 0;

	/**
	 * @brief Removes the given data element by its index location
	 */
	virtual void remove(size_t index) = 0;
};
}  // namespace ds
