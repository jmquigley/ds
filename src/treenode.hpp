/**
 * @brief a special node case used by tree structures.
 *
 * This file provides the node structured that will be used by Tree
 * type structures
 */

#pragma once

#include <node.hpp>
#include <property.hpp>

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @brief A specialized node class used in tree structures.
 *
 * TreeNode extends the base Node class to support both binary trees
 * (via left/right pointers inherited from Node) and general trees
 * (via a vector of children).
 *
 * @tparam T The type of data stored in the node
 */
template<typename T>
class TreeNode : public Node<T> {
	/// @brief A vector to hold child nodes in a general tree
	PROPERTY(_children, Children, std::vector<T>);

public:

	/**
	 * @brief Default constructor
	 */
	TreeNode() : Node<T>() {}

	/**
	 * @brief Constructor with data initialization
	 * @param data The data to store in this node
	 */
	TreeNode(T data) : Node<T>(data) {}

	/**
	 * @brief Constructor with parent node and data
	 * @param parent Weak pointer to parent node
	 * @param data The data to store in this node
	 */
	TreeNode(std::weak_ptr<TreeNode<T>> parent, T data)
		: Node<T>(std::static_pointer_cast<Node<T>>(parent), data) {}

	/**
	 * @brief Comprehensive constructor for a complete node initialization
	 * @param parent Weak pointer to parent node
	 * @param left Shared pointer to left child node
	 * @param right Shared pointer to right child node
	 * @param flags Node flags for additional properties
	 * @param data The data to store in this node
	 */
	TreeNode(std::weak_ptr<TreeNode<T>> parent, std::shared_ptr<TreeNode<T>> left,
			 std::shared_ptr<TreeNode<T>> right, ByteFlag flags, T data)
		: Node<T>::_data(data),
		  Node<T>::_flags(flags),
		  Node<T>::_left(std::static_pointer_cast<Node<T>>(left)),
		  Node<T>::_right(std::static_pointer_cast<Node<T>>(right)),
		  Node<T>::_parent(std::static_pointer_cast<Node<T>>(parent)) {}

	/**
	 * @brief A convenience method for returning the child structure
	 * @return A vector of children related to this tree's node
	 */
	std::vector<T> children() const {
		return this->_children;
	}
};

}  // namespace ds
