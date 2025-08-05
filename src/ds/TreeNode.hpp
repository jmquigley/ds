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
		copy(other);
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
	 * @brief Copy assignment operator for TreeNode
	 *
	 * Assigns the contents of another TreeNode to this one, including all
	 * tree structure properties and data. This performs a shallow copy,
	 * maintaining the same references to child nodes.
	 *
	 * @param other The TreeNode to copy from
	 * @return Reference to this TreeNode after assignment
	 */
	TreeNode<T> &operator=(const TreeNode<T> &other) {
		return this->copy(other);
	}

	/**
	 * @brief Move assignment operator for TreeNode
	 *
	 * Transfers ownership of resources from another TreeNode to this one.
	 * The source node is left in a valid but empty state after the move
	 * operation. All tree structure and relationships are preserved in the
	 * target node.
	 *
	 * @param other The TreeNode to move resources from
	 * @return Reference to this TreeNode after move assignment
	 */
	TreeNode<T> &operator=(TreeNode<T> &&other) {
		return this->move(std::move(other));
	}

	/**
	 * @brief Equality comparison operator
	 *
	 * Compares this TreeNode with another to determine if they are equal.
	 * Two nodes are considered equal if they have the same data value
	 * (uses T's equality operator).
	 *
	 * @param other The TreeNode to compare with
	 * @return true if the nodes contain equal data, false otherwise
	 */
	bool operator==(const TreeNode<T> &other) const {
		return this->_data == other._data;
	}

	/**
	 * @brief Inequality comparison operator
	 *
	 * Compares this TreeNode with another to determine if they are not equal.
	 * Two nodes are considered unequal if they have different data values
	 * (uses T's inequality operator).
	 *
	 * @param other The TreeNode to compare with
	 * @return true if the nodes contain different data, false otherwise
	 */
	bool operator!=(const TreeNode<T> &other) const {
		return this->_data != other._data;
	}

	/**
	 * @brief Less-than comparison operator
	 *
	 * Compares this TreeNode with another to establish an ordering.
	 * This operator uses T's less-than operator to compare the nodes' data
	 * values. Useful for sorting and ordered containers.
	 *
	 * @param other The TreeNode to compare with
	 * @return true if this node's data is less than other's data, false
	 * otherwise
	 */
	bool operator<(const TreeNode<T> &other) const {
		return this->_data < other._data;
	}

	/**
	 * @brief Greater-than comparison operator
	 *
	 * Compares this TreeNode with another to establish an ordering.
	 * This operator uses T's greater-than operator to compare the nodes' data
	 * values. Useful for sorting and ordered containers.
	 *
	 * @param other The TreeNode to compare with
	 * @return true if this node's data is greater than other's data, false
	 * otherwise
	 */
	bool operator>(const TreeNode<T> &other) const {
		return this->_data > other._data;
	}

	/**
	 * @brief Override copy to include parent relationship
	 *
	 * @param other The TreeNode to copy from
	 * @returns A reference to this TreeNode after copying
	 */
	TreeNode<T> &copy(const TreeNode<T> &other) override {
		if (this != &other) {
			BaseNode<T, TreeNode>::copy(other);
			this->_parent = other._parent;
		}
		return *this;
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
	std::shared_ptr<TreeNode<T>> deepcopy() override {
		auto base = BaseNode<T, TreeNode>::deepcopy();
		base->_parent = this->_parent;
		return base;
	}

	/**
	 * @brief Override move to include parent relationship
	 *
	 * @param other The TreeNode to move from
	 * @returns A reference to this TreeNode after moving
	 */
	TreeNode<T> &move(TreeNode<T> &&other) override {
		if (this != &other) {
			BaseNode<T, TreeNode>::move(std::move(other));
			this->_parent = std::move(other._parent);
			other._parent.reset();
		}
		return *this;
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
