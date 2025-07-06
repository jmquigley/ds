#pragma once

#include <Collection.hpp>
#include <Iterable.hpp>
#include <TreeNode.hpp>
#include <cstddef>
#include <limits>
#include <property.hpp>
#include <vector>

namespace ds {

/**
 * @class BaseTree
 * @brief Abstract interface for tree structures
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T, template<class> class C>
class BaseTree : public Collection<T, C>, public Iterable<T, C> {
	/// @brief The current height of the tree
	PROPERTY_D(_height, Height, size_t, = 0);

public:

	BaseTree() : Collection<T, TreeNode>() {}

	/**
	 * @brief Constructor for Tree that passes along a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	BaseTree(Comparator<T> comparator) : Collection<T, C>(comparator) {}
};

}  // namespace ds
