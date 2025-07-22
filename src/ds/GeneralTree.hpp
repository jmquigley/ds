#pragma once

#include <ds/str.h>

#include <algorithm>
#include <ds/BaseTree.hpp>
#include <ds/GeneralTreeNode.hpp>
#include <ds/Match.hpp>
#include <ds/Queue.hpp>
#include <initializer_list>
#include <string>
#include <tuple>

namespace ds {

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

	std::shared_ptr<GeneralTree<T>> newNode(
		std::string key, std::shared_ptr<GeneralTreeNode<T>> &parent) {
		return this->newNode(key, {}, parent);
	}

public:

	GeneralTree() : BaseTree<T, GeneralTreeNode>() {
		std::shared_ptr<ds::GeneralTreeNode<T>> root =
			std::make_shared<ds::GeneralTreeNode<T>>();
		this->_root = root;
	}

	GeneralTree(Comparator<T> &comparator) : GeneralTree<T>() {}

	GeneralTree(std::initializer_list<std::tuple<std::string, T>> il)
		: GeneralTree<T>() {
		for (auto const &[key, data]: il) {
			this->insert(key, data);
		}
	}

	virtual ~GeneralTree() {
		this->clear();
	}

	virtual GeneralTree<T> &operator+=(const T data) override {
		// TODO: implement operator+= for GeneralTree
		return *this;
	}

	void array(std::vector<T> &out) {
		// TODO: implement the array function in GeneralTree
	}

	std::vector<T> array() {
		// TODO: implement the array function in GeneralTree
		std::vector<T> out;
		return out;
	}

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

	void clear() {
		// TODO: implement clear() for GeneralTree
	}

	bool contains(T data) const {
		// TODO: implement contains data for GeneralTree
		return false;
	}

	bool contains(std::string key) const {
		// TODO: implement contains() for GeneralTree
		return false;
	}

	virtual Match<T, GeneralTreeNode> find(T data) const override {
		// TODO: implement find() for GeneralTree
		// search the whole tree for instances of data
		Match<T, GeneralTreeNode> match;
		return match;
	}

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

	std::string json() const {
		// TODO: implement json() for GeneralTree
		return "";
	}

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

		std::vector<std::string> keys =
			splitStringOnDelimiters(key, delimiters);

		this->_height = std::max(this->_height, keys.size());

		std::shared_ptr<GeneralTreeNode<T>> node = this->_root;
		for (auto &k: keys) {
			if (!node->hasChild(k)) {
				// The key doesn't exist, so insert a new child and save the
				// child as the new key
				node = node->addChild(k, {});
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

	T remove(std::string key) {
		// TODO: implement remove() for GeneralTree
		T data {};
		return data;
	}

	virtual T removeAt(size_t index,
					   std::shared_ptr<GeneralTreeNode<T>> tnode = nullptr) {
		// TODO: implement removeAt special case
		T data {};
		return data;
	}

	virtual T removeValue(T value) {
		// TODO: implmenet removeValue special case
		T data {};
		return data;
	}

	std::string str() const {
		// TODO: implement str() for GeneralTree
		return "";
	}
};

}  // namespace ds
