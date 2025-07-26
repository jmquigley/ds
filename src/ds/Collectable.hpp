#pragma once

#include <cstddef>
#include <string>

namespace ds {

/**
 * @class Collectable
 * @brief An interface for all collection type objects.
 *
 * This class is the minimum contract required for all Collection objects.
 *
 * @tparam T the data type that will be used while manipulating the class.
 */
template<typename T>
class Collectable {
public:

	/**
	 * @brief Retrieves teh data from the collection at the given index position
	 * @param index (`size_t`) the index position within the collection
	 * @returns the data element located at the given index
	 * @pure
	 */
	virtual T at(size_t index) = 0;

	/**
	 * @brief Clears all elements from the collection, making it empty.
	 * @pure
	 */
	virtual void clear() = 0;

	/**
	 * @brief Checks a container for the existence of the given T element
	 * @param data (`T`) the data element to find within the collection
	 * @return true if found in the container, otherwise false
	 * @pure
	 */
	virtual bool contains(T data) const = 0;

	/**
	 * @brief Check if the collection is empty
	 * @return true if the colleciton is empty, otherwise false
	 * @pure
	 */
	virtual inline bool empty() const = 0;

	/**
	 * @brief Insert the given data into a collection at back of the collection
	 * @param data The element to insert
	 * @pure
	 */
	virtual void insert(T data) = 0;

	/**
	 * @brief returns a JSON representation of the given collection.
	 * @returns a std::string that contains a json representation of the
	 * collection
	 * @pure
	 */
	virtual std::string json() const = 0;

	/**
	 * @brief retrieves the element at the end of the collection
	 * @return a `T` data element
	 * @pure
	 * @throws std::bad_weak_ptr if the requested back pointer is not available
	 */
	virtual inline T maximum() const = 0;

	/**
	 * @brief retrieves the element at the front of the collection
	 * @return a `T` data element
	 * @pure
	 */
	virtual inline T minimum() const = 0;

	/**
	 * @brief Removes the given data element by its index location
	 * @param index (`size_t`) the location within the collection to remove
	 * @returns the `T` value that was removed
	 * @pure
	 */
	virtual T removeAt(size_t index) = 0;

	/**
	 * @brief Removes the first instance of the given value from the list.
	 * @param value (`T`) a data value to find and remove from the list
	 * @returns the `T` value that was removed
	 * @pure
	 */
	virtual T removeValue(T value) = 0;

	/**
	 * @brief Returns a string representation of the collection's contents.
	 * @return a `std::string` A string describing the collection.
	 * @pure
	 */
	virtual std::string str() const = 0;
};

}  // namespace ds
