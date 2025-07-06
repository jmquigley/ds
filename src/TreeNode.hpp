#pragma once

#include <BaseNode.hpp>
#include <memory>
#include <property.hpp>
#include <vector>

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
class TreeNode : public BaseNode<T, TreeNode> {
	/// @brief A vector to hold child nodes in a general tree
	PROPERTY_SCOPED(_children, Children, std::vector<T>, protected:);
	/// @brief A shared pointer to the parent node.
	PROPERTY_SCOPED(_parent, Parent, std::weak_ptr<TreeNode<T>>, protected:);

public:

	/**
	 * @brief Default constructor
	 */
	TreeNode() : BaseNode<T, TreeNode>() {}

	/**
	 * @brief Constructor with data initialization
	 * @param data The data to store in this node
	 */
	TreeNode(T data) : BaseNode<T, TreeNode>(data) {}

	/**
	 * @brief Constructor with parent node and data
	 * @param parent Weak pointer to parent node
	 * @param data The data to store in this node
	 */
	TreeNode(std::weak_ptr<TreeNode<T>> parent, T data) : BaseNode<T, TreeNode>() {}

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
		: BaseNode<T, TreeNode>::_data(data),
		  BaseNode<T, TreeNode>::_flags(flags),
		  BaseNode<T, TreeNode>::_left(std::static_pointer_cast<BaseNode<T, TreeNode>>(left)),
		  BaseNode<T, TreeNode>::_right(std::static_pointer_cast<BaseNode<T, TreeNode>>(right)),
		  _parent(parent) {}

	/**
	 * @brief A convenience method for returning the child structure
	 * @return A vector of children related to this tree's node
	 */
	std::vector<T> children() const {
		return this->_children;
	}

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
	TreeNode<T> deepcopy() const {
		TreeNodeBuilder<T> builder;
		auto newNode = builder.withData(this->_data).withFlags(this->_flags).build();
		return *newNode;
	}

	/**
	 * @brief convenience method to retrieve the parent pointer
	 * @returns a shared_pointer to to the parent object of this node
	 */
	inline std::shared_ptr<TreeNode<T>> parent() const {
		return this->_parent.lock();
	}
};

}  // namespace ds
