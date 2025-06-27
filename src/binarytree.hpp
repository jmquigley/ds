/**
 * @brief Defines the abstract interface for tree structures
 *
 */

#pragma once

#include <cstddef>
#include <limits>
#include <vector>

#include "node.hpp"
#include "property.hpp"
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
class BinaryTree : public Tree<T> {
private:

	Node<T> insertDelegate(T data, std::shared_ptr<Node<T>> &node,
						   std::shared_ptr<Node<T>> &parent) {}

	std::shared_ptr<Node<T>> newNode(T data, std::shared_ptr<Node<T>> &parent) {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);
	}

public:

	void insert(T data) {}
};

}  // namespace ds
