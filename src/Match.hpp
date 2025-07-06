#pragma once

#include <Node.hpp>
#include <memory>
#include <property.hpp>

namespace ds {

/**
 * @class Match
 * @brief A container class to hold the results of a find operation in a data structure
 *
 * Match is designed to provide a consistent interface for returning search results.
 * It not only indicates whether an item was found, but also provides additional context
 * such as the value found, the node containing the value, and its position in the
 * data structure.
 *
 * @tparam T The type of data stored within the Match
 */
template<typename T>
class Match {
	/// @brief The data value found during the search operation
	PROPERTY_D(data, Data, T, {0});

	/// @brief Flag indicating whether the search operation was successful
	PROPERTY_D(_found, Found, bool, {false});

	/// @brief The position or index where the item was found (if applicable)
	PROPERTY_D(index, Index, size_t, {0});

	/// @brief Weak pointer to the node containing the found value
	PROPERTY(node, Node, std::weak_ptr<Node<T>>);

public:

	/**
	 * @brief A convenience function to check if the search operation was successful
	 *
	 * This method provides a more intuitive way to check the success status
	 * compared to directly accessing the Found property.
	 *
	 * @returns true if this Match object holds a found value, otherwise false
	 */
	inline bool found() const {
		return this->getFound();
	}
};
}  // namespace ds
