#pragma once

#include <ds/BaseNode.hpp>
#include <ds/BinaryTree.hpp>
#include <ds/Comparable.hpp>
#include <ds/OrderedSet.hpp>
#include <ds/Path.hpp>
#include <ds/Replicate.hpp>
#include <ds/property.hpp>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
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
	public std::enable_shared_from_this<GeneralTreeNode<T>>,
	public Comparable<GeneralTreeNode<T>>,
	public Replicate<T, GeneralTreeNode<T>> {
	/// @brief The data payload of the node.
	PROPERTY_SCOPED_WITH_DEFAULT_NO_CONST(data, Data, T, protected:, {});

	/// @brief a unique key used by each general tree node
	PROPERTY_SCOPED_WITH_DEFAULT(key, Key, std::string, protected:, {""});

	/// @brief the path from the root to this node
	PROPERTY_SCOPED(path, Path, Path, protected:);

private:

	/// @brief A shared pointer to the parent node.
	std::weak_ptr<GeneralTreeNode<T>> _parent;

protected:

	/// @brief A map to hold child nodes indexed by their keys
	OrderedSet<GeneralTreeNode<T>> _children;

public:

	/**
	 * @brief Default constructor
	 * Creates a node with empty key and default data
	 */
	GeneralTreeNode()
		: GeneralTreeNode<T>(std::weak_ptr<GeneralTreeNode<T>>(), "", {}, "") {}

	/**
	 * @brief Constructor with key only construction.
	 *
	 * This constructor is used to create a search key GeneralTreeNode
	 *
	 * @param key (`std::string`) The unique identifier for this node
	 */
	GeneralTreeNode(const std::string &key)
		: GeneralTreeNode<T>(std::weak_ptr<GeneralTreeNode<T>>(), key, {}, "") {
	}

	/**
	 * @brief Constructor with key, data, and path string
	 * @param key (`std::string`) The unique identifier for this node
	 * @param data (`T`) The data to store in this node
	 * @param path (`std::string`) the path to root for this child record
	 */
	GeneralTreeNode(const std::string &key, T data, const std::string &path)
		: GeneralTreeNode<T>(std::weak_ptr<GeneralTreeNode<T>>(), key, data,
							 path) {}

	/**
	 * @brief Constructor with key, data, and path object
	 * @param key (`std::string`) The unique identifier for this node
	 * @param data (`T`) The data to store in this node
	 * @param path (`Path`) the path object to the root for this child record
	 */
	GeneralTreeNode(const std::string &key, T data, const Path &path)
		: GeneralTreeNode<T>(key, data, path.path()) {}

	/**
	 * @brief Full constructor with parent, key, path, and data
	 * @param parent A weak pointer to the parent node
	 * @param key The unique identifier for this node
	 * @param data The data to store in this node
	 * @param path (`std::string`) the path to root for this child record
	 */
	GeneralTreeNode(const std::weak_ptr<GeneralTreeNode<T>> &parent,
					const std::string &key, T data, const std::string &path)
		: _data(data), _key(key), _path(path), _parent(parent) {}

	/**
	 * @brief Copy constructor for GeneralTree
	 * @param other (`GeneralTreeNode<T> &`) The node to copy from
	 */
	GeneralTreeNode(const GeneralTreeNode<T> &other) : GeneralTreeNode<T>() {
		this->copy(other);
	}

	/**
	 * @brief Move constructor for GeneralTree
	 * @param other (`GeneralTreeNode<T> &&`) The node to move
	 */
	GeneralTreeNode(GeneralTreeNode<T> &&other) noexcept
		: GeneralTreeNode<T>() {
		this->move(std::move(other));
	}

	/**
	 * @brief Destructor
	 * Clears all children and data
	 */
	virtual ~GeneralTreeNode() {
		clear();
	}

	/**
	 * @brief Assignment operator for general tree
	 * @param other (`GeneralTreeNode &`) Reference to the node to assign from
	 * @return Reference to this node after assignment
	 */
	GeneralTreeNode<T> &operator=(const GeneralTreeNode<T> &other) {
		return this->copy(other);
	}

	/**
	 * @brief Move operator for general tree
	 * @param other (`GeneralTree<T> &&`) an rvalue general tree refrence
	 * @return Reference to this node after assignment
	 */
	GeneralTreeNode<T> &operator=(GeneralTreeNode<T> &&other) noexcept {
		return this->move(std::move(other));
	}

	/**
	 * @brief Equality operator
	 * @param other The node to compare with
	 * @return true if the keys are equal, false otherwise
	 */
	bool operator==(const GeneralTreeNode<T> &other) const noexcept override {
		return this->_key == other._key;
	}

	/**
	 * @brief Inequality operator
	 * @param other The node to compare with
	 * @return true if the keys are not equal, false otherwise
	 */
	bool operator!=(const GeneralTreeNode<T> &other) const noexcept override {
		return this->_key != other._key;
	}

	/**
	 * @brief Less than operator for GeneralTreeNode
	 * @param other The node to compare with
	 * @return true if this node's key is less than other's key
	 */
	bool operator<(const GeneralTreeNode<T> &other) const noexcept override {
		return this->_key < other._key;
	}

	/**
	 * @brief Less than or eqqual operator for GeneralTreeNode
	 * @param other The node to compare with
	 * @return true if this node's key is less than or equal to the other's key
	 */
	bool operator<=(const GeneralTreeNode<T> &other) const noexcept override {
		return this->_key <= other._key;
	}

	/**
	 * @brief Greater than operator
	 * @param other The node to compare with
	 * @return true if this node's key is greater than other's key
	 */
	bool operator>(const GeneralTreeNode<T> &other) const noexcept override {
		return this->_key > other._key;
	}

	/**
	 * @brief Greater than or eqqual operator for GeneralTreeNode
	 * @param other The node to compare with
	 * @return true if this node's key is greater than or equal to the other's
	 * key
	 */
	bool operator>=(const GeneralTreeNode<T> &other) const noexcept override {
		return this->_key >= other._key;
	}

	/**
	 * @brief Adds a child node with the given key and data
	 * @param key The unique key for the new child
	 * @param data The data for the new child
	 * @param path (`std::string`) the path to root for this child record
	 */
	void addChild(std::string key, T data, std::string path) {
		std::shared_ptr<GeneralTreeNode<T>> parent = this->shared_from_this();
		std::cout << "parent: " << parent << std::endl;
		_children.insert(GeneralTreeNode(parent, key, data, path));
	}

	/**
	 * @brief Gets the current list of children from the GeneralTreeNode
	 * @returns a `std::map` to the children in this node
	 */
	OrderedSet<GeneralTreeNode<T>> &children() {
		return this->_children;
	}

	/**
	 * @brief Clears all children and resets this node's data
	 * Releases all child nodes and resets the node to its initial state
	 */
	void clear() {
		_children.clear();
		_key = "";
		_path = "";
		_data = {};
		_parent.reset();
	}

	/**
	 * @brief A convenience method to copy elements from one general tree node
	 * to another.
	 * @param other (`GeneralTreeNode<T> &`)  The general tree node to copy from
	 * @returns a reference to the this pointer for this general tree node
	 */
	virtual GeneralTreeNode<T> &copy(const GeneralTreeNode<T> &other) override {
		if (this != &other) {
			this->_children = other._children;
			this->_key = other._key;
			this->_path = other._path;
			this->_data = other._data;
			this->_parent = other._parent;
		}

		return *this;
	}

	/**
	 * @brief Creates a deep copy of this node and its children
	 * @return A shared pointer to the newly created copy
	 */
	virtual std::shared_ptr<GeneralTreeNode<T>> deepcopy() override {
		auto copy = std::make_shared<GeneralTreeNode<T>>(
			this->_key, this->_data, this->_path);
		copy->_children = this->_children;
		return copy;
	}

	/**
	 * @brief Retrieves a child node by its key
	 * @param key The key of the child to retrieve
	 * @return A reference to the general tree node related to this key
	 * @throws a std::runtime_error if the requested child doesn't exist
	 */
	GeneralTreeNode<T> &getChild(std::string key) {
		auto match = this->_children.find(GeneralTreeNode<T>(key));
		if (match.found()) {
			return match.reference();
		}

		throw std::runtime_error("Invalid child name requested");
	}

	/**
	 * @brief Retrieves a child node by its index position
	 * @param index the location within the list child nodes
	 * @return A reference to the general tree node related to this index
	 * @throws a std::out_of_range if the requested child doesn't exist
	 */
	GeneralTreeNode<T> &getChild(size_t index) {
		if (_children.size() == 0 || index >= _children.size()) {
			throw std::out_of_range("Invalid child position index requested");
		}

		return _children[index];
	}

	/**
	 * @brief Gets all children of this node
	 * @return A vector containing shared pointers to all child nodes
	 */
	std::vector<GeneralTreeNode<T>> getChildrenArray() {
		std::vector<GeneralTreeNode<T>> out;

		for (const auto &value: _children) {
			out.push_back(value);
		}
		return out;
	}

	/**
	 * @brief Checks the child list for the existence of a key
	 * @param key (`std::string`) the key value for the node in the tree
	 * @returns true if the key is in the child list, otherwise false
	 */
	bool hasChild(std::string key) {
		return this->_children.contains(GeneralTreeNode<T>(key));
	}

	/**
	 * @brief Moves content from another general tree node to this one
	 * @param other The general tree node to move from
	 * @return Reference to this node after the move operation
	 */
	virtual GeneralTreeNode<T> &move(GeneralTreeNode<T> &&other) override {
		if (this != &other) {
			// this->_children = std::move(other._children);
			this->_key = std::move(other._key);
			this->_path = std::move(other._path);
			this->_data = std::move(other._data);
			this->_parent = std::move(other._parent);

			this->_children.each([&](size_t index, GeneralTreeNode<T> &gtn) {
				gtn.setParent(this->shared_from_this());
			});

			// Reset other
			other._children.clear();
			other._key = "";
			other._path = "";
			other._data = T {};
			other._parent.reset();
		}

		return *this;
	}

	/**
	 * @brief a special print function that is used by the comparable interface
	 * @param os an `std::ostream &` object that will perform the print
	 */
	virtual void print(std::ostream &os) const override {
		os << this->str();
	}

	/**
	 * @brief Removes a child node with the specified key
	 * @param key The key of the child to remove
	 */
	void removeChild(std::string key) {
		std::shared_ptr<GeneralTreeNode<T>> search =
			std::make_shared<GeneralTreeNode<T>>(key);

		_children.removeValue(GeneralTreeNode<T>(key));
	}

	/**
	 * @brief gives a string representation of the general tree node
	 * @returns a string value that represents the contents of the node
	 */
	std::string str() const {
		std::stringstream ss;

		ss << "[" << std::quoted("data") << ":" << this->_data << "]";

		return ss.str();
	}

	/**
	 * @brief Gets the total number of immediate children
	 * @return The number of child nodes
	 */
	size_t totalChildren() const {
		return _children.size();
	}

	/**
	 * @brief Convenience method to retrieve the parent pointer
	 * @returns a shared_pointer to to the parent object of this node
	 */
	inline std::shared_ptr<GeneralTreeNode<T>> parent() const {
		return this->_parent.lock();
	}

	/**
	 * @brief Setting for the parent pointer of a node
	 * @param value `std::shared_ptr<TreeNode<T>>` to set as the parent
	 */
	void setParent(const std::shared_ptr<GeneralTreeNode<T>> &value) {
		this->_parent = value;
	}
};

}  // namespace ds

namespace std {

/**
 * @brief Specialized hash object for unordered_map objects
 */
template<typename T>
struct hash<ds::GeneralTreeNode<T>> {
	/**
	 * @brief a specialized hash function used by unordered_map to deal with
	 * `GeneralTreeNode` class object comparisons.
	 *
	 * @param gtn (`GeneralTreeNode<T> &`) a reference to the general tree
	 * object to be hashed
	 * @returns a hash value for the `GeneralTreeNode<T>` object key value.
	 */
	size_t operator()(const ds::GeneralTreeNode<T> &gtn) const {
		return hash<std::string>()(gtn.path().str());
	}
};

}  // namespace std
