#pragma once

#include <ds/BaseNode.hpp>
#include <ds/property.hpp>
#include <memory>
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
protected:

	/// @brief A shared pointer to the parent node.
	std::weak_ptr<TreeNode<T>> _parent;

public:

	/**
	 * @brief Default constructor
	 */
	TreeNode()
		: BaseNode<T, TreeNode>(), _parent(std::weak_ptr<TreeNode<T>>()) {}

	/**
	 * @brief Constructor with data initialization
	 * @param data The data to store in this node
	 */
	TreeNode(T data)
		: BaseNode<T, TreeNode>(data), _parent(std::weak_ptr<TreeNode<T>>()) {}

	/**
	 * @brief Constructor with parent node and data
	 * @param parent Weak pointer to parent node
	 * @param data The data to store in this node
	 */
	TreeNode(const std::weak_ptr<TreeNode<T>> &parent, T data)
		: BaseNode<T, TreeNode>(nullptr, nullptr, (ByteFlag)0, data),
		  _parent(parent) {}

	/**
	 * @brief Comprehensive constructor for a complete node initialization
	 * @param parent Weak pointer to parent node
	 * @param left Shared pointer to left child node
	 * @param right Shared pointer to right child node
	 * @param flags Node flags for additional properties
	 * @param data The data to store in this node
	 */
	TreeNode(const std::weak_ptr<TreeNode<T>> &parent,
			 std::shared_ptr<TreeNode<T>> &left,
			 std::shared_ptr<TreeNode<T>> &right, ByteFlag flags, T data)
		: BaseNode<T, TreeNode>(left, right, flags, data), _parent(parent) {}

	/**
	 * @brief copy constructor for the TreeNode class
	 * @param other the tree node to copy
	 */
	TreeNode(const TreeNode<T> &other) : BaseNode<T, TreeNode>(other) {
		this->operator=(other);
	}

	/**
	 * @brief Move constructor for the TreeNode class
	 */
	TreeNode(const TreeNode<T> &&other) : BaseNode<T, TreeNode>(other) {}

	/**
	 * @brief TreeNode desstrutor
	 */
	virtual ~TreeNode() {}

	/**
	 * @brief equal operator for the TreeNode class
	 * @param tn the tree node to copy
	 * @returns a reference the this pointer for the object
	 */
	TreeNode<T> operator=(TreeNode<T> &tn) {
		this->_parent = tn._parent;
		// BaseNode<T, TreeNode>::operator=(tn);
		return *static_cast<TreeNode<T> *>(this);
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
		auto newNode =
			builder.withData(this->_data).withFlags(this->_flags).build();
		return *newNode;
	}

	/**
	 * @brief convenience method to retrieve the parent pointer
	 * @returns a shared_pointer to to the parent object of this node
	 */
	inline std::shared_ptr<TreeNode<T>> parent() const {
		return this->_parent.lock();
	}

	/**
	 * @brief setting for the parent pointer of a node
	 * @param value `std::shared_ptr<TreeNode<T>>` to set as the parent
	 */
	void setParent(std::shared_ptr<TreeNode<T>> value) {
		this->_parent = value;
	}
};

}  // namespace ds
