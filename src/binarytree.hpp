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
 * @class BinaryTree
 * @brief A binary tree class that uses the Red-Black algorithm.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class BinaryTree : public Tree<T> {
private:

	/**
	 * @brief Recursive helper method for inserting nodes into the tree
	 * @param data Data to be inserted
	 * @param node Current node in recursion
	 * @param parent Parent of the current node
	 * @return Node<T> The newly inserted node
	 */
	Node<T> insertDelegate(T data, std::shared_ptr<Node<T>> &node,
						   std::shared_ptr<Node<T>> &parent) {}

	/**
	 * @brief Creates a new node with the specified data and parent
	 * @param data Data to store in the new node
	 * @param parent Parent node for the new node
	 * @return std::shared_ptr<Node<T>> Shared pointer to the newly created node
	 */
	std::shared_ptr<Node<T>> newNode(T data, std::shared_ptr<Node<T>> &parent) {
		std::shared_ptr<ds::Node<T>> node;
		NodeBuilder<T> builder;

		node = builder.withData(data).withParent(parent);
		return node;
	}

public:

	/**
	 * @brief Inserts a new element into the binary tree
	 *
	 * @param data The data to insert into the tree
	 */
	void insert(T data) {}
};

}  // namespace ds
