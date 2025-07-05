/**
 * @brief Defines the abstract interface for tree structures
 *
 */

#pragma once

#include <collection.hpp>
#include <cstddef>
#include <iterable.hpp>
#include <limits>
#include <node.hpp>
#include <property.hpp>
#include <treenode.hpp>
#include <vector>

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Tree
 * @brief Abstract interface for tree structures
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class Tree : public Collection<T>, public Iterable<T> {
	/// @brief The current height of the tree
	PROPERTY_D(_height, Height, size_t, = 0);

public:

	Tree() : Collection<T>() {}

	/**
	 * @brief Constructor for Tree that passes along a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	Tree(Comparator<T> comparator) : Collection<T>(comparator) {}
};

}  // namespace ds
