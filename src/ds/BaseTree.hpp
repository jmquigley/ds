#pragma once

#include <cstddef>
#include <ds/Collection.hpp>
#include <ds/TreeNode.hpp>
#include <ds/property.hpp>
#include <limits>
#include <vector>

namespace ds {

/**
 * @class BaseTree
 * @brief Abstract interface for tree structures
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T, template<class> class C>
class BaseTree : public Collection<T, C> {
	/// @brief The current height of the tree
	// PROPERTY_WITH_DEFAULT(_height, Height, size_t, {0});

protected:

	size_t _height;

public:

	BaseTree() : Collection<T, C>(), _height(0) {}

	/**
	 * @brief Constructor for Tree that passes along a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	BaseTree(Comparator<T> &comparator) : Collection<T, C>(comparator) {}

	virtual ~BaseTree() = default;

	/**
	 * @brief Calculates the height of the tree
	 *
	 * The height of a tree is defined as the number of edges on the longest
	 * path from the root node to any leaf node. An empty tree has a height of
	 * 0, and a tree with only a root node also has a height of 0.
	 *
	 * This is a pure virtual function that must be implemented by all derived
	 * classes. Different tree structures may have different algorithms for
	 * calculating height, but all implementations should adhere to the standard
	 * definition of tree height.
	 *
	 * Expected behavior:
	 * - Empty trees should return 0
	 * - Trees with only a root node should return 0
	 * - For all other trees, return the longest path length from root to any
	 * leaf
	 *
	 * @return The height of the tree as a non-negative integer
	 * @pure
	 */
	virtual size_t height() = 0;
};

}  // namespace ds
