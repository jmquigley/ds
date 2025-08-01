#pragma once

#include <ds/Match.hpp>

namespace ds {

/**
 * @class Searchable
 * @brief An interface for all searchable collection types
 *
 * This interface defines the minimum contract required for collections that
 * support search operations. Classes implementing this interface can be
 * searched for elements of type T, returning detailed information about the
 * search results.
 *
 * The Searchable interface enables a standard approach to searching across
 * different collection types, allowing for consistent search behavior
 * regardless of the underlying data structure.
 *
 * @tparam T The type of elements that can be searched for
 * @tparam C The container/node type used by the collection, which will be
 * referenced in search results
 *
 * @note Implementing classes should define their search strategy based on their
 *       internal structure (e.g., linear search, binary search, hash-based
 * lookup)
 *
 * @par Example usage:
 * @code{.cpp}
 * // Using a class that implements Searchable
 * List<int> myList = {1, 2, 3, 4, 5};
 * Match<int, Node> result = myList.find(3);
 * if (result.found()) {
 *     std::cout << "Found element at index: " << result.getIndex() <<
 * std::endl;
 * }
 * @endcode
 */
template<typename T, template<class> class C>
class Searchable {
	/**
	 * @brief Searches for an element in the collection
	 *
	 * Performs a search operation to find the specified element within the
	 * collection. The search strategy depends on the implementing class's data
	 * structure.
	 *
	 * @param data The element to search for in the collection
	 * @return Match<T, C> A Match object containing:
	 *         - Whether the element was found (via found() method)
	 *         - The matching data if found
	 *         - The index/position where it was found (if applicable)
	 *         - A reference to the container/node that contains the element
	 *
	 * @note If the element is not found, the returned Match object will
	 * indicate this through its found() method returning false.
	 *
	 * @note The time complexity of the search operation depends on the
	 * implementing class's data structure and search algorithm. Common
	 * complexities include:
	 *       - O(n) for linear search in unsorted collections
	 *       - O(log n) for binary search in sorted collections
	 *       - O(1) for hash-based collections (average case)
	 */
	virtual Match<T, C> find(T data) = 0;
};

}  // namespace ds
