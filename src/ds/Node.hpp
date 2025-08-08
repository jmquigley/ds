#pragma once

#include <ds/BaseNode.hpp>
#include <ds/BaseNodeBuilder.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace ds {

/**
 * @class Node
 * @brief A generic node class template for collection classes.
 *
 * This class extends BaseNode to provide a concrete implementation for various
 * collection data structures. It maintains the same interface as BaseNode while
 * providing specific functionality for linked data structures.
 *
 * @tparam T The type of data stored within the node.
 */
template<typename T>
class Node : public BaseNode<T, Node> {
public:

	/**
	 * @brief Default constructor
	 *
	 * Creates an empty node with default-initialized data and null child
	 * pointers.
	 */
	Node() : BaseNode<T, Node>() {}

	/**
	 * @brief Constructor with data initialization
	 *
	 * Creates a node containing the specified data value with null child
	 * pointers.
	 *
	 * @param data The data to store in this node
	 */
	Node(T data) : BaseNode<T, Node>(data) {}

	/**
	 * @brief Comprehensive constructor for a complete node initialization
	 *
	 * Creates a node with all fields explicitly specified, including left and
	 * right child nodes, flags for additional properties, and data value.
	 *
	 * @param left Shared pointer to left child node
	 * @param right Shared pointer to right child node
	 * @param flags Node flags for additional properties
	 * @param data The data to store in this node
	 */
	Node(const std::shared_ptr<Node<T>> &left,
		 const std::shared_ptr<Node<T>> &right, ByteFlag flags, T data)
		: BaseNode<T, Node>(left, right, flags, data) {}

	/**
	 * @brief Copy constructor for the Node class
	 *
	 * Creates a new node as a copy of an existing one, including all properties
	 * and child references.
	 *
	 * @param other The node to copy from
	 */
	Node(const Node<T> &other) : BaseNode<T, Node>(other) {}

	/**
	 * @brief Move constructor for the Node class
	 *
	 * Creates a new node by transferring resources from an existing node,
	 * leaving the source node in a valid but unspecified state.
	 *
	 * @param other The node to move resources from
	 */
	Node(Node<T> &&other) noexcept : BaseNode<T, Node>(std::move(other)) {}

	/**
	 * @brief Node destructor
	 *
	 * Properly cleans up resources associated with this node.
	 * Child nodes are not automatically deleted as they may be referenced
	 * elsewhere.
	 */
	virtual ~Node() = default;

	/**
	 * @brief Copy assignment operator
	 *
	 * Assigns the contents of another node to this node.
	 *
	 * @param other The node to copy from
	 * @return Reference to this node after assignment
	 */
	Node<T> &operator=(const Node<T> &other) {
		BaseNode<T, Node>::operator=(other);
		return *this;
	}

	/**
	 * @brief Move assignment operator
	 *
	 * Transfers ownership of resources from another node to this node.
	 *
	 * @param other The node to move resources from
	 * @return Reference to this node after assignment
	 */
	Node<T> &operator=(Node<T> &&other) noexcept {
		BaseNode<T, Node>::operator=(std::move(other));
		return *this;
	}
};

}  // namespace ds
