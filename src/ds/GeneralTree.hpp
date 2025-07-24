#pragma once

#include <ds/str.h>

#include <algorithm>
#include <ds/BaseTree.hpp>
#include <ds/GeneralTreeNode.hpp>
#include <ds/Match.hpp>
#include <ds/Queue.hpp>
#include <ds/constants.hpp>
#include <initializer_list>
#include <sstream>
#include <string>
#include <tuple>

namespace ds {

/**
 * @class GeneralTree
 * @brief A general tree data structure implementation that supports
 * hierarchical key-based storage
 *
 * The GeneralTree class provides a flexible tree structure where nodes can have
 * any number of children. It supports hierarchical path-based keys (like file
 * paths) for organizing and accessing data. Each node in the tree can store a
 * value of type T and is identified by a string key.
 *
 * Key features:
 * - Path-based insertion using delimiters (e.g., "/", "\", "|")
 * - Breadth-first and depth-first traversal mechanisms
 * - Key-based and value-based searching
 * - JSON serialization for data interchange
 *
 * @tparam T The type of data stored within each node of the general tree.
 */
template<typename T>
class GeneralTree : public BaseTree<T, GeneralTreeNode> {
private:

	/**
	 * @brief Creates a new general tree node instance.
	 *
	 * @param key (`std::string`) the key to insert into the tree
	 * @param data (`T`) the data that will be added with this node
	 * @param parent (`std::shared_ptr<GeneralTreeNode<T>> &`) the parent
	 * associated to this node.
	 * @returns a new shared pointer reference to the created node.
	 */
	std::shared_ptr<GeneralTreeNode<T>> newNode(
		std::string key, T data, std::shared_ptr<GeneralTreeNode<T>> &parent) {
		std::shared_ptr<GeneralTreeNode<T>> node;
		GeneralTreeNodeBuilder<T> builder;

		node = builder.withKey(key).withData(data).withParent(parent).build();

		return node;
	}

	/**
	 * @brief Creates a new general tree node instance without data.
	 *
	 * @param key (`std::string`) the key to insert into the tree
	 * @param parent (`std::shared_ptr<GeneralTreeNode<T>> &`) the parent
	 * associated to this node.
	 * @returns a new shared pointer reference to the created node.
	 */
	std::shared_ptr<GeneralTree<T>> newNode(
		std::string key, std::shared_ptr<GeneralTreeNode<T>> &parent) {
		return this->newNode(key, {}, parent);
	}

public:

	/**
	 * @brief Default constructor for the general tree.
	 *
	 * Initializes the tree with an empty root node.
	 */
	GeneralTree() : BaseTree<T, GeneralTreeNode>() {
		std::shared_ptr<ds::GeneralTreeNode<T>> root =
			std::make_shared<ds::GeneralTreeNode<T>>();
		this->_root = root;
	}

	/**
	 * @brief Constructor with comparator.
	 *
	 * @param comparator A comparator function for comparing elements of type T.
	 */
	GeneralTree(Comparator<T> &comparator) : GeneralTree<T>() {}

	/**
	 * @brief Initializer list constructor.
	 *
	 * Constructs a tree with initial key-value pairs.
	 *
	 * @param il Initializer list of key-value pairs.
	 */
	GeneralTree(std::initializer_list<std::tuple<std::string, T>> il)
		: GeneralTree<T>() {
		for (auto const &[key, data]: il) {
			this->insert(key, data);
		}
	}

	/**
	 * @brief Destructor for GeneralTree.
	 *
	 * Cleans up all allocated resources.
	 */
	virtual ~GeneralTree() {
		this->clear();
	}

	/**
	 * @brief Adds a data item to the tree.
	 *
	 * @param data The data to add to the tree.
	 * @return Reference to this tree after the operation.
	 */
	virtual GeneralTree<T> &operator+=(const T data) override {
		// TODO: implement operator+= for GeneralTree
		return *this;
	}

	/**
	 * @brief Outputs the tree elements into a vector.
	 *
	 * @param out Reference to a vector where the tree elements will be stored.
	 */
	void array(std::vector<T> &out) {
		// TODO: implement the array function in GeneralTree
	}

	/**
	 * @brief Returns all tree elements as a vector.
	 *
	 * @return A vector containing all tree elements.
	 */
	std::vector<T> array() {
		// TODO: implement the array function in GeneralTree
		std::vector<T> out;
		return out;
	}

	/**
	 * @brief Retrieves the element at the specified index.
	 *
	 * @param index The index of the element to retrieve.
	 * @return The element at the specified index.
	 */
	virtual T at(size_t index) override {
		// TODO: implement at for GeneralTree
		T data {};
		return data;
	}

	/**
	 * @brief performs a breadth first traversal of the tree.
	 *
	 * Breadth-first search is a tree traversal algorithm that explores all
	 * nodes at the present depth level before moving on to nodes at the next
	 * depth level. This is in contrast to depth-first search algorithms (like
	 * pre-order, in-order, and post-order traversals) which explore as far as
	 * possible along each branch before backtracking.
	 *
	 * @param callback a function pointer that will be executed on each node as
	 * it is encountered.
	 */
	template<typename Callback>
	void breadth(Callback callback) const {
		std::shared_ptr<GeneralTreeNode<T>> node = this->_root;
		ds::Queue<std::shared_ptr<GeneralTreeNode<T>>> q {};

		// load the root children into the queue
		for (auto const &[key, data]: node->getChildrenRef()) {
			q.enqueue(data);
		}

		while (!q.empty()) {
			node = q.dequeue();

			// allows for a callback with a short circuit return value
			if constexpr (std::is_same_v<decltype(callback(*node)), bool>) {
				if (!callback(*node)) {
					return;	 // short circuit if callback returns false
				}
			} else {
				callback(*node);
			}

			if (node->totalChildren() > 0) {
				for (auto const &[key, data]: node->getChildrenRef()) {
					q.enqueue(data);
				}
			}
		}
	}

	/**
	 * @brief Searches for a node with the specified key using breadth-first
	 * search.
	 *
	 * @param key The key to search for.
	 * @return A Match object containing the result of the search.
	 */
	Match<T, GeneralTreeNode> breadthSearch(std::string key) const {
		Match<T, GeneralTreeNode> match;

		this->breadth([&](auto &node) {
			if (node->key() == key) {
				match.setData(node->getData());
				match.setFound(true);
				match.setRef(node);
				return false;
			}

			return true;
		});

		return match;
	}

	/**
	 * @brief Clears all nodes from the tree.
	 */
	void clear() {
		// TODO: implement clear() for GeneralTree
	}

	/**
	 * @brief Checks if the tree contains the specified data.
	 *
	 * @param data The data to search for.
	 * @return true if the data is found, false otherwise.
	 */
	bool contains(T data) const {
		// TODO: implement contains data for GeneralTree
		return false;
	}

	/**
	 * @brief Checks if the tree contains a node with the specified key.
	 *
	 * @param key The key to search for.
	 * @return true if a node with the key is found, false otherwise.
	 */
	bool contains(std::string key) const {
		// TODO: implement contains() for GeneralTree
		return false;
	}

	/**
	 * @brief Finds a node containing the specified data.
	 *
	 * @param data The data to search for.
	 * @return A Match object containing the result of the search.
	 */
	virtual Match<T, GeneralTreeNode> find(T data) const override {
		// TODO: implement find() for GeneralTree
		// search the whole tree for instances of data
		Match<T, GeneralTreeNode> match;
		return match;
	}

	/**
	 * @brief Finds a node with the specified key.
	 *
	 * @param key The key to search for.
	 * @return A Match object containing the result of the search.
	 */
	Match<T, GeneralTreeNode> find(std::string key) const {
		// TODO: implement find() for GeneralTree
		Match<T, GeneralTreeNode> match;
		return match;
	}

	/**
	 * @brief the current height of the tree
	 * @returns the current height of the tree
	 */
	virtual size_t height() {
		return this->_height;
	}

	/**
	 * @brief Generates a JSON representation of the tree.
	 *
	 * @return A string containing the JSON representation.
	 */
	std::string json() const {
		// TODO: implement json() for GeneralTree
		return "";
	}

	/**
	 * @brief Inserts data directly into the root node.
	 *
	 * @param data The data to insert.
	 */
	void insert(T data) {
		// TODO: special case insert into the root node directly
	}

	/**
	 * @brief Inserts a key-data pair into the general tree.
	 *
	 * This function takes a key, splits it into components using the provided
	 * delimiters, and traverses or builds the tree accordingly. Each component
	 * of the split key represents a level in the tree hierarchy.
	 *
	 * Algorithm:
	 * 1. If the key is an empty string, the function returns without action
	 * 2. Split the key into components using the provided delimiters
	 * 3. Start traversal from the root node
	 * 4. For each key component:
	 *    a. If the current node doesn't have a child with this key, create a
	 * new child b. If the child already exists, traverse to that child
	 * 5. Set the data value on the final node reached
	 *
	 * Example:
	 * For key "root/folder/file" with delimiter "/":
	 * - Creates or traverses to node "root"
	 * - Then creates or traverses to node "folder" under "root"
	 * - Finally creates or traverses to node "file" under "folder" and sets its
	 * data
	 *
	 * @param key The key to insert, which will be split using delimiters
	 * @param data The data value to associate with the final node
	 * @param delimiters Vector of delimiter strings to split the key (defaults
	 * to {"\\", "/", "|"})
	 */
	void insert(std::string key, T data,
				std::vector<std::string> delimiters = {"\\", "/", "|"}) {
		if (key == "") {
			return;
		}

		std::stringstream ss;
		std::vector<std::string> keys =
			splitStringOnDelimiters(key, delimiters);

		this->_height = std::max(this->_height, keys.size());

		std::shared_ptr<GeneralTreeNode<T>> node = this->_root;
		for (auto &k: keys) {
			ss << k << constants::SEPARATOR;

			if (!node->hasChild(k)) {
				// The key doesn't exist, so insert a new child and save the
				// child as the new key
				node = node->addChild(k, {}, ss.str());
				this->_size++;
			} else {
				// Child exists, so get a reference to it and don't insert
				// again
				node = node->getChild(k);
			}
		}

		// The last node encountered will always get the data value
		node->setData(data);
	}

	/**
	 * @brief Removes a node with the specified key from the tree.
	 *
	 * @param key The key of the node to remove.
	 * @return The data that was stored in the removed node.
	 */
	T remove(std::string key) {
		// TODO: implement remove() for GeneralTree
		T data {};
		return data;
	}

	/**
	 * @brief Removes a node at the specified index.
	 *
	 * @param index The index of the node to remove.
	 * @param tnode Optional starting node for the removal operation.
	 * @return The data that was stored in the removed node.
	 */
	virtual T removeAt(size_t index,
					   std::shared_ptr<GeneralTreeNode<T>> tnode = nullptr) {
		// TODO: implement removeAt special case
		T data {};
		return data;
	}

	/**
	 * @brief Removes a node containing the specified value.
	 *
	 * @param value The value to search for and remove.
	 * @return The data that was stored in the removed node.
	 */
	virtual T removeValue(T value) {
		// TODO: implmenet removeValue special case
		T data {};
		return data;
	}

	/**
	 * @brief Generates a string representation of the tree.
	 *
	 * @return A string representation of the tree.
	 */
	std::string str() const {
		// TODO: implement str() for GeneralTree
		return "";
	}
};

}  // namespace ds
