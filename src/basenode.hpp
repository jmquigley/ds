/**
 * @brief Defines the BaseNode class template for all other types of collection nodes
 *
 */

#pragma once

#include <bitflag.hpp>
#include <builder.hpp>
#include <helpers.hpp>
#include <iomanip>
#include <iostream>
#include <memory>
#include <property.hpp>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @enum NodeFlag
 * @brief Bit flags for node properties used in tree data structures.
 *
 * Defines flags that can be set on nodes to determine their characteristics.
 * Implemented using bit positions for memory-efficient storage of boolean properties.
 */
enum NodeFlag : unsigned char {
	Color = 1 << 0,	 // 0 = RED, 1 = BLACK
};

/**
 * @class BaseNode
 * @brief A generic node class template for tree-like data structures.
 *
 * This class represents a single node in a tree, capable of holding generic data,
 * a unique identifier, and references to parent, left, and right child nodes.
 * It uses the PROPERTY macro for automatic getter/setter generation.
 *
 * @tparam T The type of data stored within the node.
 */
template<typename T, template<class> class C>
class BaseNode {
	/// @brief The data payload of the node.
	PROPERTY_SCOPED(_data, Data, T, protected:);
	/// @brief flags used to determine bit properties in a node
	PROPERTY_SCOPED(_flags, Flags, ByteFlag, protected:);
	/// @brief A shared pointer to the left child node.
	PROPERTY_SCOPED(_left, Left, std::shared_ptr<C<T>>, protected:);
	/// @brief A shared pointer to the right child node.
	PROPERTY_SCOPED(_right, Right, std::shared_ptr<C<T>>, protected:);
	/// @brief A shared pointer to the parent node.
	PROPERTY_SCOPED(_parent, Parent, std::weak_ptr<C<T>>, protected:);

private:

	/**
	 * @brief Copy assignment helper function.
	 *
	 * Creates a deep copy of the source node into this node. The current node
	 * is initialized with a new ID before copying all properties from the source.
	 * This ensures that the resulting node is a distinct entity with the same
	 * content as the source.
	 *
	 * @param src The source Node object to copy from
	 * @return Reference to this node after the copy operation
	 */
	C<T> &copy(const C<T> &src) {
		this->_data = src._data;
		this->_parent = src._parent;
		this->_right = src._right;
		this->_left = src._left;

		return *this;
	}

public:

	/**
	 * @brief Default constructor for Node.
	 *
	 * Initializes parentId to empty, parent, left, and right to nullptr,
	 * and generates a unique ID.
	 */
	BaseNode() : _flags(0), _left(nullptr), _right(nullptr), _parent() {}

	/**
	 * @brief Constructor for Node with initial data.
	 *
	 * Calls the main constructor with parent, left, and right as nullptr.
	 * @param data The data to be stored in the node.
	 */
	BaseNode(T data) : BaseNode(std::weak_ptr<C<T>>(), nullptr, nullptr, ByteFlag(), data) {}

	/**
	 * @brief Constructor for Node with a parent and initial data.
	 *
	 * Calls the main constructor with left and right as nullptr.
	 * Note: This constructor makes a copy of the 'parent' Node object,
	 * it does not take a pointer or shared_ptr. This might be a design
	 * consideration depending on usage.
	 *
	 * @param parent The parent node (copied by value).
	 * @param data The data to be stored in the node.
	 */
	BaseNode(std::weak_ptr<C<T>> parent, T data)
		: BaseNode(parent, nullptr, nullptr, ByteFlag(), data) {}

	/**
	 * @brief Full constructor for Node.
	 *
	 * Initializes parent, left, right, and data, and generates a unique ID.
	 * If a parent pointer is provided, its ID is set as the parentId.
	 *
	 * @param parent A pointer to the parent node. Can be nullptr.
	 * @param left A pointer to the left child node. Can be nullptr.
	 * @param right A pointer to the right child node. Can be nullptr.
	 * @param flags initial internal flag settings for the new node
	 * @param data The data to be stored in the node.
	 */
	BaseNode(std::weak_ptr<C<T>> parent, std::shared_ptr<C<T>> left, std::shared_ptr<C<T>> right,
			 ByteFlag flags, T data)
		: _data(data), _flags(flags), _left(left), _right(right), _parent(parent) {}

	/**
	 * @brief Destructor for Node.
	 *
	 * Currently empty, but can be extended for cleanup if needed.
	 */
	~BaseNode() {
		this->clear();
	}

	/**
	 * @brief Move constructor for Node.
	 *
	 * Creates a new node by transferring ownership of resources from another node.
	 * The source node will be left in a valid but unspecified state after the move.
	 *
	 * @param other The source Node object to move resources from
	 */
	BaseNode(const C<T> &other) {
		copy(other);
	}

	/**
	 * @brief Move constructor for Node.
	 *
	 * Efficiently transfers ownership of resources from the source node to this node.
	 * - Preserves the generated ID of the moved-from node
	 * - Transfers data and relationship pointers
	 * - Updates parent-child relationships to maintain tree integrity
	 *
	 * @param other (`Node<T>`) The Node object to move from (will be left in a valid but
	 * unspecified state)
	 */
	BaseNode(C<T> &&other) {
		move(std::move(other));
	}

	/**
	 * @brief Overloads the stream insertion operator for Node objects.
	 *
	 * Allows printing a Node object directly to an output stream,
	 * using its `str()` method for representation.
	 * @param st The output stream.
	 * @param node The Node object to print.
	 * @return A reference to the output stream.
	 */
	friend std::ostream &operator<<(std::ostream &st, const C<T> &node) {
		return st << node.str();
	}

	/**
	 * @brief Copy assignment operator.
	 *
	 * Assigns the contents of another node to this node using deep copying.
	 * This operator creates a new deep copy of the right-hand side node,
	 * maintaining the unique identity of this node while adopting all data
	 * and relationships from the source node.
	 *
	 * @param rhs The right-hand side Node object to copy from
	 * @return Reference to this node after the assignment
	 */
	C<T> &operator=(const C<T> &rhs) {
		copy(rhs);
		return *this;
	}

	/**
	 * @brief Move assignment operator.
	 *
	 * Transfers ownership of all resources from the right-hand side node to this node.
	 * This is more efficient than copy assignment as it avoids deep copying by
	 * moving resources from the source node, leaving it in a valid but unspecified state.
	 *
	 * @param rhs The right-hand side Node object to move resources from
	 * @return Reference to this node after the assignment
	 */
	C<T> &operator=(C<T> &&rhs) {
		move(std::move(rhs));
		return *this;
	}

	/**
	 * @brief When dereferencing a node this operator will return the data in the node
	 * @returns The `T` data that is associated with this node.
	 */
	T &operator*() {
		return this->_data;
	}

	/**
	 * @brief Clears the node's identifiers and pointers, then re-initializes a new ID.
	 *
	 * Sets parentId to empty, parent, right, left to nullptr,
	 */
	void clear() {
		this->_right.reset();
		this->_left.reset();
		this->_parent.reset();
	}

	/**
	 * @brief Convenience method to get the data stored in the node
	 * @returns a `T &` that references the data in the node
	 */
	T &data() {
		return this->_data;
	}

	/**
	 * Checks if this node is black.
	 * @return true if the node is black, false otherwise
	 */
	bool isBlack() const {
		return _flags[0] == 1;
	}

	/**
	 * Checks if this node is red.
	 * @return true if the node is red, false otherwise
	 */
	bool isRed() const {
		return _flags[0] == 0;
	}

	/**
	 * @brief Convenience method to get the left child pointer of this node
	 * @returns a std::shared_ptr<Node<T>> object that represents the left
	 * child node pointer.
	 */
	inline std::shared_ptr<C<T>> left() const {
		return this->_left;
	}

	/**
	 * @brief Helper function to implement move semantics.
	 *
	 * Transfers ownership of all resources from the source node to this node,
	 * including ID, data, parent references, and child nodes. This operation
	 * is more efficient than copying as it avoids deep copying of resources.
	 *
	 * @param src The source Node object to move resources from
	 * @return Reference to this node after the move operation
	 */
	C<T> &move(C<T> &&src) {
		this->data = std::move(src.data);
		this->parent = std::move(src.parent);
		this->right = std::move(src.right);
		this->left = std::move(src.left);

		return *this;
	}

	/**
	 * @brief convenience method to retrieve the parent pointer
	 * @returns a shared_pointer to to the parent object of this node
	 */
	inline std::shared_ptr<C<T>> parent() const {
		return this->_parent.lock();
	}

	/**
	 * @brief Convenience method to get the right child pointer of this node
	 * @returns a std::shared_ptr<Node<T>> object that represents the right
	 * child node pointer.
	 */
	inline std::shared_ptr<C<T>> right() const {
		return this->_right;
	}

	/**
	 * Sets this node's color to red.
	 * In the Red-Black tree, red is represented by unsetting the Color flag.
	 */
	void setRed() {
		this->_flags.unset(NodeFlag::Color);
	}

	/**
	 * Sets this node's color to black.
	 * In the Red-Black tree, black is represented by setting the Color flag.
	 */
	void setBlack() {
		this->_flags.set(NodeFlag::Color);
	}

	/**
	 * @brief Returns a string representation of the node.
	 *
	 * Currently, it formats the node's data into a simple JSON-like string.
	 * @return A string representing the node's content.
	 */
	std::string str() const {
		std::stringstream ss;

		ss << "{";
		ss << std::quoted("data") << ":" << _data << ",";

		if (this->isRed()) {
			ss << std::quoted("color") << ":" << std::quoted("red");
		} else {
			ss << std::quoted("color") << ":" << std::quoted("black");
		}
		ss << "}";

		return ss.str();
	}
};

}  // namespace ds
