/**
 * @brief Defines the abstract interface for tree structures
 *
 */

#pragma once

#include <limits>
#include <vector>

#include "property.hpp"
#include "stddef.h"
#include "tree.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Tree
 * @brief A binary tree class that uses the Red-Black algorithm.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class BinaryTree : public Tree<T> {};

}  // namespace ds
