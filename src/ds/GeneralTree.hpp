#pragma once

#include <ds/str.h>

#include <ds/BaseTree.hpp>
#include <ds/GeneralTreeNode.hpp>
#include <ds/Match.hpp>
#include <string>

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
		this->_root = newNode("", {}, nullptr);
	}

	GeneralTree(Comparator<T> &comparator) : GeneralTree<T>() {}

	virtual ~GeneralTree() {
		this->clear();
	}

	template<typename Callback>
	void breadth(Callback callback) const {
		// TODO: implement breadth traversal through the tree
	}

	Match<T, GeneralTreeNode> breadthSearch(std::string key) const {
		// TODO: implement breadthSearch for GeneralTree
	}

	void clear() {
		// TODO: implement clear() for GeneralTree
	}

	bool contains(std::string key) const {
		// TODO: implement contains() for GeneralTree
		return false;
	}

	Match<T, GeneralTreeNode> find(std::string key) const {
		// TODO: implmenet find() for GeneralTree
		Match<T, GeneralTreeNode> match;
		return match;
	}

	virtual size_t height() const {
		// TODO: implement height() for GeneralTree
		return 0;
	}

	std::string json() const {
		// TODO: implement json() for GeneralTree
		return "";
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

		std::shared_ptr<GeneralTreeNode<T>> node = this->_root;
		for (auto &k: keys) {
			if (!node->hasChild(k)) {
				// The key doesn't exist, so insert a new child and save the
				// child as the new key
				node = node->addChild(k, {});
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

	std::string str() const {
		// TODO: implement str() for GeneralTree
		return "";
	}
};

}  // namespace ds
