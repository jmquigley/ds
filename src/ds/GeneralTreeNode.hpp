#pragma once

#include <ds/BinaryTree.hpp>
#include <ds/Comparator.hpp>
#include <ds/property.hpp>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace ds {

/**
 * @class GeneralTreeNode
 * @brief A templated class representing a node in a general tree structure
 *
 * This class provides the functionality for nodes in a general tree where each
 * node can have multiple children identified by string keys.
 *
 * @tparam T The data type stored in the tree node
 */
template<typename T>
class GeneralTreeNode :
	public std::enable_shared_from_this<GeneralTreeNode<T>> {
	/// @brief The data payload of the node.
	PROPERTY_SCOPED_WITH_DEFAULT(data, Data, T, protected:, {});

	/// @brief a unique key used by each general tree node
	PROPERTY_SCOPED(key, Key, std::string, protected:);

private:

	/// @brief A shared pointer to the parent node.
	GeneralTreeNode<T> *_parent;

protected:

	/// @brief A map to hold child nodes indexed by their keys
	std::map<std::string, std::shared_ptr<GeneralTreeNode<T>>> _children;

public:

	/**
	 * @brief Default constructor
	 * Creates a node with empty key and default data
	 */
	GeneralTreeNode() : GeneralTreeNode<T>(nullptr, "", {}) {}

	/**
	 * @brief Constructor with key and data
	 * @param key The unique identifier for this node
	 * @param data The data to store in this node
	 */
	GeneralTreeNode(std::string key, T data)
		: GeneralTreeNode<T>(nullptr, key, data) {}

	/**
	 * @brief Full constructor with parent, key and data
	 * @param parent A weak pointer to the parent node
	 * @param key The unique identifier for this node
	 * @param data The data to store in this node
	 */
	GeneralTreeNode(GeneralTreeNode<T> *parent, std::string key, T data)
		: _data(data), _key(key), _parent(parent) {}

	/**
	 * @brief Copy constructor
	 * @param gtn The node to copy from
	 */
	GeneralTreeNode(GeneralTreeNode<T> &gtn) : GeneralTreeNode<T>() {
		this->operator=(gtn);
	}

	/**
	 * @brief Destructor
	 * Clears all children and data
	 */
	virtual ~GeneralTreeNode() {
		clear();
	}

	/**
	 * @brief Assignment operator
	 * @param gtn The node to assign from
	 * @return Reference to this node after assignment
	 */
	GeneralTreeNode &operator=(GeneralTreeNode<T> &gtn) {
		this->_children = gtn._children;
		this->_key = gtn._key;
		this->_data = gtn._data;
		return *this;
	}

	/**
	 * @brief Equality operator
	 * @param other The node to compare with
	 * @return true if the keys are equal, false otherwise
	 */
	bool operator==(const GeneralTreeNode<T> &other) {
		return this->_key == other._key;
	}

	/**
	 * @brief Inequality operator
	 * @param other The node to compare with
	 * @return true if the keys are not equal, false otherwise
	 */
	bool operator!=(const GeneralTreeNode<T> &other) {
		return this->_key != other._key;
	}

	/**
	 * @brief Less than operator
	 * @param other The node to compare with
	 * @return true if this node's key is less than other's key
	 */
	bool operator<(const GeneralTreeNode<T> &other) {
		return this->_key < this->_key;
	}

	/**
	 * @brief Greater than operator
	 * @param other The node to compare with
	 * @return true if this node's key is greater than other's key
	 */
	bool operator>(const GeneralTreeNode<T> &other) {
		return this->_key > this->_key;
	}

	/**
	 * @brief Adds a child node with the given key and data
	 * @param key The unique key for the new child
	 * @param data The data for the new child
	 */
	void addChild(std::string key, T data) {
		_children[key] = std::make_shared<GeneralTreeNode<T>>(this, key, data);
	}

	/**
	 * @brief Clears all children and resets this node's data
	 */
	void clear() {
		for (auto &[key, value]: _children) {
			value.reset();
		}
		_children.clear();
		_key = "";
		_data = {};
		_parent = nullptr;
	}

	/**
	 * @brief Retrieves a child node by its key
	 * @param key The key of the child to retrieve
	 * @return A shared pointer to the child node
	 */
	std::shared_ptr<GeneralTreeNode<T>> getChild(std::string key) {
		return _children[key];
	}

	/**
	 * @brief Gets all children of this node
	 * @return A vector containing shared pointers to all child nodes
	 */
	std::vector<std::shared_ptr<GeneralTreeNode<T>>> getChildren() {
		std::vector<std::shared_ptr<GeneralTreeNode<T>>> out;
		for (const auto &[key, value]: _children) {
			out.push_back(value);
		}
		return out;
	}

	/**
	 * @brief Removes a child node with the specified key
	 * @param key The key of the child to remove
	 */
	void removeChild(std::string key) {
		std::shared_ptr<GeneralTreeNode<T>> tnode = _children[key];
		tnode.reset();
		_children.erase(key);
	}

	/**
	 * @brief Gets the total number of immediate children
	 * @return The number of child nodes
	 */
	size_t totalChildren() const {
		return _children.size();
	}

	/**
	 * @brief convenience method to retrieve the parent pointer
	 * @returns a shared_pointer to to the parent object of this node
	 */
	inline GeneralTreeNode<T> *parent() const {
		return this->_parent;
	}

	/**
	 * @brief setting for the parent pointer of a node
	 * @param value `std::shared_ptr<TreeNode<T>>` to set as the parent
	 */
	void setParent(GeneralTreeNode<T> &value) {
		this->_parent = value;
	}
};

}  // namespace ds
