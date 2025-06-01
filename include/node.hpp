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
#include <vector>

#include "property.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

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
	/// @brief The unique identifier of the node.
	PROPERTY(id, Id, std::string);
	/// @brief A shared pointer to the left child node.
	PROPERTY(left, Left, std::shared_ptr<Node<T>>);
	/// @brief The ID of the parent node.
	PROPERTY(parentId, ParentId, std::string);
	/// @brief A shared pointer to the right child node.
	PROPERTY(right, Right, std::shared_ptr<Node<T>>);
	/// @brief A shared pointer to the parent node.
	PROPERTY(parent, Parent, std::shared_ptr<Node<T>>);

private:

	/// @brief A vector to hold child nodes (though left/right pointers are primarily used, this
	/// allows for N-ary representation if populated).
	std::vector<T> children;

	/**
	 * @brief Initializes the node by generating a unique ID.
	 */
	void init() {
		uuid_t uuid;
		char uuidStr[UUID_STR_LEN];

		// Creates a unique identifier for a node
		uuid_generate_random(uuid);
		uuid_unparse(uuid, uuidStr);
		id = uuidStr;
	}

public:

	/**
	 * @brief Default constructor for Node.
	 *
	 * Initializes parentId to empty, parent, left, and right to nullptr,
	 * and generates a unique ID.
	 */
	Node() : parentId(""), parent(nullptr), left(nullptr), right(nullptr) {
		init();
	}

	/**
	 * @brief Constructor for Node with initial data.
	 *
	 * Calls the main constructor with parent, left, and right as nullptr.
	 * @param data The data to be stored in the node.
	 */
	Node(T data) : Node(nullptr, nullptr, nullptr, data) {}

	/**
	 * @brief Constructor for Node with a parent and initial data.
	 *
	 * Calls the main constructor with left and right as nullptr.
	 * Note: This constructor makes a copy of the 'parent' Node object,
	 * it does not take a pointer or shared_ptr. This might be a design
	 * consideration depending on usage.
	 * @param parent The parent node (copied by value).
	 * @param data The data to be stored in the node.
	 */
	Node(Node<T> parent, T data) : Node(parent, nullptr, nullptr, data) {}

	/**
	 * @brief Full constructor for Node.
	 *
	 * Initializes parent, left, right, and data, and generates a unique ID.
	 * If a parent pointer is provided, its ID is set as the parentId.
	 * @param parent A pointer to the parent node. Can be nullptr.
	 * @param left A pointer to the left child node. Can be nullptr.
	 * @param right A pointer to the right child node. Can be nullptr.
	 * @param data The data to be stored in the node.
	 */
	Node(Node<T> *parent, Node<T> *left, Node<T> *right, T data)
		: parent(parent), left(left), right(right), data(data) {
		init();
		if (parent) {
			parentId = parent->getParentId();
		}
	}

	/**
	 * @brief Destructor for Node.
	 *
	 * Currently empty, but can be extended for cleanup if needed.
	 */
	~Node() {}

	/**
	 * @brief Copy constructor for Node.
	 *
	 * Creates a new Node object by performing a member-wise copy of an existing Node.
	 * - `std::string` members (`id`, `parentId`) are deep copied.
	 * - `std::shared_ptr` members (`parent`, `left`, `right`) result in shared ownership.
	 * - `std::vector<T>` member (`children`) is deep copied (its elements are copied).
	 * - The `T` member (`data`) is copied according to `T`'s own copy semantics.
	 *
	 * @param node The existing Node object to copy from.
	 */
	Node(Node<T> &node) {
		this->data = node.data;
		this->id = node.id;
		this->parentId = node.parentId;
		this->parent = node.parent;
		this->right = node.right;
		this->left = node.left;
		this->children = node.children;
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
	 * @brief Clears the node's identifiers and pointers, then re-initializes a new ID.
	 *
	 * Sets ID and parentId to empty, parent, right, left to nullptr,
	 * clears the children vector, and generates a new unique ID for the node.
	 */
	void clear() {
		this->id = "";
		this->parentId = "";
		this->parent = nullptr;
		this->right = nullptr;
		this->left = nullptr;
		this->children.clear();
		init();	 // Generate a new ID after clearing
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
	 * @brief Sets the ID for the Node being built.
	 * @param id The ID to set.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withId(std::string id) {
		node.setId(id);
		return *this;
	}

	/**
	 * @brief Sets the parent ID for the Node being built.
	 * @param parentId The parent ID to set.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withParentId(std::string parentId) {
		node.setParentId(parentId);
		return *this;
	}

	/**
	 * @brief Sets the parent Node (via shared_ptr) for the Node being built.
	 * @param parent A shared pointer to the parent Node.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withParent(std::shared_ptr<Node<T>> parent) {
		node.setParent(parent);
		return *this;  // Note: Original code was missing return *this;
	}

	/**
	 * @brief Sets the right child Node (via shared_ptr) for the Node being built.
	 * @param right A shared pointer to the right child Node.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withRight(std::shared_ptr<Node<T>> right) {
		node.setRight(right);
		return *this;  // Note: Original code was missing return *this;
	}

	/**
	 * @brief Sets the left child Node (via shared_ptr) for the Node being built.
	 * @param left A shared pointer to the left child Node.
	 * @return A reference to the NodeBuilder for chaining.
	 */
	NodeBuilder &withLeft(std::shared_ptr<Node<T>> left) {
		node.setLeft(left);
		return *this;  // Note: Original code was missing return *this;
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
