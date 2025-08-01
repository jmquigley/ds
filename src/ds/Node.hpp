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
 * @tparam T The type of data stored within the node.
 */
template<typename T>
class Node : public BaseNode<T, Node> {
public:

	/**
	 * @brief Default constructor
	 */
	Node() : BaseNode<T, Node>() {}

	/**
	 * @brief Constructor with data initialization
	 * @param data The data to store in this node
	 */
	Node(T data) : BaseNode<T, Node>(data) {}

	/**
	 * @brief Comprehensive constructor for a complete node initialization
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
	 */
	Node(const Node<T> &other) : BaseNode<T, Node>(other) {}

	/**
	 * @brief Move constructor for the Node class
	 */
	Node(Node<T> &&other) : BaseNode<T, Node>(other) {}

	/**
	 * @brief Node destructor
	 */
	virtual ~Node() {}

	/**
	 * @brief Creates a deep copy of this node
	 *
	 * This function creates a true deep copy of the node,
	 * including properly copying the data and color state.
	 * The new node will not have any parent or child relationships
	 * since those should be established by the tree structure.
	 *
	 * @returns a copy of the Node<T> that was created
	 */
	Node<T> deepcopy() const {
		NodeBuilder<T> builder;
		auto newNode =
			builder.withData(this->_data).withFlags(this->_flags).build();
		return *newNode;
	}
};

}  // namespace ds
