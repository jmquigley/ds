/**
 * @file node.hpp
 * @brief Defines the Node class template for tree-like data structures and its associated
 * NodeBuilder.
 *
 * This file provides the core components for building a generic N-ary tree
 * structure (though primarily focused on binary tree elements like left/right/parent)
 * with unique identifiers and property-based data access.
 */

#pragma once

#include <uuid/uuid.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "bitflag.hpp"
#include "helpers.hpp"
#include "property.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {


enum NodeFlag : size_t {
    Color = 1 << 0,   // 0 = RED, 1 = BLACK
};


/**
 * @class Node
 * @brief A generic node class template for tree-like data structures.
 *
 * This class represents a single node in a tree, capable of holding generic data,
 * a unique identifier, and references to parent, left, and right child nodes.
 * It uses the PROPERTY macro for automatic getter/setter generation.
 *
 * @tparam T The type of data stored within the node.
 */
template<typename T>
class Node {
	// Doxygen for PROPERTY macro generated members:
	/// @brief The data payload of the node.
	PROPERTY(data, Data, T);
	/// @brief flags used to determine bit properties in a node
	PROPERTY(flags, Flags, BitFlag);
	/// @brief A shared pointer to the left child node.
	PROPERTY(left, Left, std::shared_ptr<Node<T>>);
	/// @brief A shared pointer to the right child node.
	PROPERTY(right, Right, std::shared_ptr<Node<T>>);
	/// @brief A shared pointer to the parent node.
	PROPERTY(parent, Parent, std::shared_ptr<Node<T>>);

private:

	/// @brief A vector to hold child nodes (though left/right pointers are primarily used, this
	/// allows for N-ary representation if populated).
	std::vector<T> children;

public:

	/**
	 * @brief Default constructor for Node.
	 *
	 * Initializes parentId to empty, parent, left, and right to nullptr,
	 * and generates a unique ID.
	 */
	Node() : flags(0), left(nullptr), right(nullptr), parent(nullptr) {}

	/**
	 * @brief Constructor for Node with initial data.
	 *
	 * Calls the main constructor with parent, left, and right as nullptr.
	 * @param data The data to be stored in the node.
	 */
	Node(T data) : Node(nullptr, nullptr, nullptr, 0, data) {}

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
	Node(std::shared_ptr<Node<T>> parent, T data) : Node(parent, nullptr, nullptr, 0, data) {}

	/**
	 * @brief Full constructor for Node.
	 *
	 * Initializes parent, left, right, and data, and generates a unique ID.
	 * If a parent pointer is provided, its ID is set as the parentId.
	 *
	 * @param parent A pointer to the parent node. Can be nullptr.
	 * @param left A pointer to the left child node. Can be nullptr.
	 * @param right A pointer to the right child node. Can be nullptr.
	 * @param data The data to be stored in the node.
	 */
	Node(std::shared_ptr<Node<T>> parent, std::shared_ptr<Node<T>> left,
		 std::shared_ptr<Node<T>> right, BitFlag flags, T data)
		: data(data), flags(flags), left(left), right(right), parent(parent) {}

	/**
	 * @brief Destructor for Node.
	 *
	 * Currently empty, but can be extended for cleanup if needed.
	 */
	~Node() {
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
	Node(const Node<T> &other) {
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
	Node(Node<T> &&other) {
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
	friend std::ostream &operator<<(std::ostream &st, const Node<T> &node) {
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
	Node<T> &operator=(const Node<T> &rhs) {
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
	Node<T> &operator=(Node<T> &&rhs) {
		move(std::move(rhs));
		return *this;
	}

	/**
	 * @brief When dereferencing a node this operator will return the data in the node
	 * @returns The `T` data that is associated with this node.
	 */
	T &operator*() {
		return this->data;
	}

	/**
	 * @brief Clears the node's identifiers and pointers, then re-initializes a new ID.
	 *
	 * Sets parentId to empty, parent, right, left to nullptr,
	 * clears the children vector, and generates a new unique ID for the node.
	 */
	void clear() {
		this->parent.reset();
		this->right.reset();
		this->left.reset();
		this->children.clear();
	}

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
	Node<T> &copy(const Node<T> &src) {
		this->data = src.data;
		this->parent = src.parent;
		this->right = src.right;
		this->left = src.left;
		this->children = src.children;

		return *this;
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
	Node<T> &move(Node<T> &&src) {
		this->data = std::move(src.data);
		this->parent = std::move(src.parent);
		this->right = std::move(src.right);
		this->left = std::move(src.left);
		this->children = std::move(src.children);

		return *this;
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
		ss << "\"data\":" << data;
		// Can add more fields here if needed, e.g., ss << ", \"id\":\"" << id << "\"";
		ss << "}";

		return ss.str();
	}
};

/**
 * @class NodeBuilder
 * @brief A builder class for constructing Node objects.
 *
 * Provides a fluent interface to set various properties of a Node
 * before building the final object.
 *
 * @tparam T The type of data for the Node being built.
 */
template<typename T>
class NodeBuilder {
private:

	/// @brief The Node object being built.
	Node<T> node;

public:

	/**
	 * @brief Sets the data for the Node being built.
	 * @param data The data to set.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withData(T data) {
		node.setData(data);
		return *this;
	}

	/**
	 * @brief Sets the parent Node (via shared_ptr) for the Node being built.
	 * @param parent A shared pointer to the parent Node.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withParent(std::shared_ptr<Node<T>> parent) {
		node.setParent(parent);
		return *this;
	}

	/**
	 * @brief Sets the right child Node (via shared_ptr) for the Node being built.
	 * @param right A shared pointer to the right child Node.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withRight(std::shared_ptr<Node<T>> right) {
		node.setRight(right);
		return *this;
	}

	/**
	 * @brief Sets the left child Node (via shared_ptr) for the Node being built.
	 * @param left A shared pointer to the left child Node.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withLeft(std::shared_ptr<Node<T>> left) {
		node.setLeft(left);
		return *this;
	}

	/**
	 * @brief Finalizes the build process and returns the constructed Node object.
	 * @return The fully configured Node object.
	 */
	Node<T> build() {
		return node;
	}
};
}  // namespace ds
