#pragma once

#include <ds/str.h>

#include <algorithm>
#include <ds/BaseTree.hpp>
#include <ds/GeneralTreeNode.hpp>
#include <ds/LRUCache.hpp>
#include <ds/Match.hpp>
#include <ds/Path.hpp>
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
	 * @brief an internal recently used cache object for path searches
	 */
	LRUCache<Path, std::shared_ptr<GeneralTreeNode<T>>> _cacheByPath;

	/**
	 * @brief an internal recently used cache object for value searches
	 */
	LRUCache<T, std::shared_ptr<GeneralTreeNode<T>>> _cacheByValue;

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
	 * Constructs a tree with initial key-value pairs. The initalizer list is
	 * a tuple of *path* and "data" values.
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
	 * @brief Searches for a node with the specified path using breadth-first
	 * search
	 *
	 * This method performs a breadth-first traversal of the tree to find a node
	 * that matches the given path exactly. Breadth-first search explores nodes
	 * level by level, starting from the root and moving outward.
	 *
	 * @param path (`Path`) The path to search for in the tree
	 * @return A Match object containing the result of the search, including:
	 *         - Whether the node was found (via found() method)
	 *         - The data associated with the node if found
	 *         - A reference to the node if found
	 *
	 * @note This method checks for exact path matches only and is
	 * case-sensitive.
	 *
	 * @par Example usage:
	 * @code{.cpp}
	 * GeneralTree<int> tree;
	 * tree.insert("root/folder/file", 42);
	 *
	 * Match<int, GeneralTreeNode> result =
	 * tree.breadthSearchByPath(Path("folder")); if (result.found()) { std::cout
	 * << "Found folder with data: " << result.getData() << std::endl;
	 * }
	 * @endcode
	 *
	 * @par Complexity:
	 *      Time: O(n) where n is the number of nodes in the tree
	 *      Space: O(w) where w is the maximum width of the tree (for queue
	 * storage)
	 */
	Match<T, GeneralTreeNode> breadthSearchByPath(const Path &path) {
		Match<T, GeneralTreeNode> match;

		// If key is empty or tree is empty, return not found
		if (path.empty() || this->_size == 0) {
			return match;
		}

		std::shared_ptr<GeneralTreeNode<T>> tnode;

		if (this->_cacheByPath.get(path, tnode)) {
			match.setData(tnode->getData());
			match.setFound(true);
			match.setSearch(path);
			match.setRef(tnode);
			return match;
		}

		this->breadth([&](auto &node) {
			if (node.path() == path) {
				match.setData(node.getData());
				match.setFound(true);
				match.setSearch(node.path());
				match.setRef(std::static_pointer_cast<GeneralTreeNode<T>>(
					node.shared_from_this()));
				this->_cacheByPath.set(path, match.getRef().lock());
				return false;
			}

			return true;
		});

		return match;
	}

	/**
	 * @brief a convenience wrapper for the `Path` version of the
	 * breadthSearchByPath
	 *
	 * This function receives a std::string and converts it to a path before
	 * using it.
	 *
	 * @param path (`std::string &`) the path string to search for
	 * @return A Match object containing the result of the search, including:
	 *         - Whether the node was found (via found() method)
	 *         - The data associated with the node if found
	 *         - A reference to the node if found
	 * @see breadthSearchByPath(const Path &)
	 */
	Match<T, GeneralTreeNode> breadthSearchByPath(
		const std::string &path) const {
		return breadthSearchByPath(Path(path));
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
	bool contains(T data) {
		Match<T, GeneralTreeNode> match;
		match = this->find(data);
		return match.found();
	}

	/**
	 * @brief Checks if the tree contains a node with the specified path.
	 *
	 * @param path (`Path &`) The path to check if it is in the tree
	 * @return true if a node with the path is found, false otherwise.
	 */
	bool containsByPath(const Path &path) {
		Match<T, GeneralTreeNode> match;
		match = this->findByPath(path);
		return match.found();
	}

	/**
	 * @brief a convenience method for search for a path using a std::string
	 * @param path (`std::string &`) the string path to check
	 * @returns true if the path is in the tree, otherwise false
	 */
	bool containsByPath(const std::string &path) {
		return containsByPath(Path(path));
	}

	/**
	 * @brief Finds a node containing the specified data value.
	 *
	 * Searches the entire tree for any node that contains the specified data
	 * value. This performs a complete tree traversal to find matching data.
	 *
	 * @param data The data value to search for
	 * @return A Match object containing the result of the search
	 *
	 * @note If multiple nodes contain the same data value, only the first
	 *       encountered during breadth-first traversal will be returned.
	 *
	 * @par Example usage:
	 * @code{.cpp}
	 * GeneralTree<int> tree;
	 * tree.insert("folder1/file", 42);
	 * tree.insert("folder2/document", 42);
	 *
	 * Match<int, GeneralTreeNode> result = tree.find(42);
	 * if (result.found()) {
	 *     // Will find the value, likely in "folder1/file" since breadth-first
	 *     // traversal typically encounters it first
	 *     std::cout << "Found 42 at path: " << result.getRef().lock()->path()
	 * << std::endl;
	 * }
	 * @endcode
	 *
	 * @par Complexity:
	 *      Time: O(n) where n is the number of nodes in the tree
	 *      Space: O(w) where w is the maximum width of the tree (for
	 * breadth-first traversal)
	 */
	virtual Match<T, GeneralTreeNode> find(T data) override {
		Match<T, GeneralTreeNode> match;

		if (this->_size == 0) {
			return match;
		}

		// Use breadth-first traversal to find the data
		this->breadth([&](auto &node) {
			// Use the comparator if available, otherwise use direct comparison
			bool isEqual =
				this->_comparator
					? (this->_comparator->compare(node.getData(), data) == 0)
					: (node.getData() == data);

			if (isEqual) {
				match.setData(data);
				match.setFound(true);
				match.setRef(std::static_pointer_cast<GeneralTreeNode<T>>(
					node.shared_from_this()));
				return false;  // Stop traversal
			}

			return true;  // Continue traversal
		});

		return match;
	}

	/**
	 * @brief Finds a node with the specified path.
	 *
	 * This function is a convenience wrapper for the breadthSearchByPath.
	 *
	 * @param path (`std::string &`) The path to search for
	 * @return A Match object containing the result of the search
	 * @see breadthSearchByPath
	 */
	Match<T, GeneralTreeNode> findByPath(const std::string &path) {
		return this->breadthSearchByPath(Path(path));
	}

	/**
	 * @brief Finds a node with the specified path.
	 *
	 * This function is a convenience wrapper for the breadthSearchByPath.
	 *
	 * @param path (`Path &`) The path to search for
	 * @return A Match object containing the result of the search
	 * @see breadthSearchByPath
	 */
	Match<T, GeneralTreeNode> findByPath(const Path &path) {
		return this->breadthSearchByPath(path);
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
	 */
	void insert(std::string key, T data) {
		if (key == "") {
			return;
		}

		Path path(key);
		Path nodePath;
		std::vector<std::string> keys = path.elements();
		std::stringstream ss;

		this->_height = std::max(this->_height, keys.size());

		std::shared_ptr<GeneralTreeNode<T>> node = this->_root;
		for (auto &k: keys) {
			nodePath.append(k);

			if (!node->hasChild(k)) {
				// The key doesn't exist, so insert a new child and save the
				// child as the new key
				node = node->addChild(k, {}, nodePath.str());
				this->_size++;

				// seed the cache with values while the cache capacity is less
				// than the collection size
				this->_cacheByPath.setCollectionSize(this->_size);
				if (this->_size < this->_cacheByPath.capacity()) {
					this->_cacheByPath.set(Path(nodePath.str()), node);
				}

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
	 * @return The data that was stored in the removed node.
	 */
	virtual T removeAt(size_t index) override {
		return this->removeAt(index, nullptr);
	}

	/**
	 * @brief Removes a node at the specified index.
	 *
	 * @param index The index of the node to remove.
	 * @param tnode Optional starting node for the removal operation.
	 * @return The data that was stored in the removed node.
	 */
	virtual T removeAt(size_t index,
					   std::shared_ptr<GeneralTreeNode<T>> tnode) {
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
