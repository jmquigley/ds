/**
 * @brief Defines the Node class template for a collection class.
 *
 * This is a concrete implementation of the Node.
 */

#pragma once

#include <basenode.hpp>
#include <builder.hpp>
#include <memory>
#include <utility>
#include <vector>

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
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
	 * @brief Constructor with parent node and data
	 * @param parent Weak pointer to parent node
	 * @param data The data to store in this node
	 */
	Node(std::weak_ptr<Node<T>> parent, T data)
		: BaseNode<T, Node>(std::static_pointer_cast<BaseNode<T, Node>>(parent), data) {}

	/**
	 * @brief Comprehensive constructor for a complete node initialization
	 * @param parent Weak pointer to parent node
	 * @param left Shared pointer to left child node
	 * @param right Shared pointer to right child node
	 * @param flags Node flags for additional properties
	 * @param data The data to store in this node
	 */
	Node(std::weak_ptr<Node<T>> parent, std::shared_ptr<Node<T>> left,
		 std::shared_ptr<Node<T>> right, ByteFlag flags, T data)
		: BaseNode<T, Node>::_data(data),
		  BaseNode<T, Node>::_flags(flags),
		  BaseNode<T, Node>::_left(std::static_pointer_cast<BaseNode<T, Node>>(left)),
		  BaseNode<T, Node>::_right(std::static_pointer_cast<BaseNode<T, Node>>(right)),
		  BaseNode<T, Node>::_parent(std::static_pointer_cast<BaseNode<T, Node>>(parent)) {}

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
		auto newNode = builder.withData(this->_data).withFlags(this->_flags).build();
		return *newNode;
	}
};

}  // namespace ds
