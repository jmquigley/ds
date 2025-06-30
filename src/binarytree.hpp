/**
 * @brief Defines a binary tree that uses the red-black algorithm
 *
 */

#pragma once

#include <cstddef>
#include <limits>
#include <string>
#include <vector>

#include "match.hpp"
#include "node.hpp"
#include "property.hpp"
#include "tree.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class BinaryTree
 * @brief A binary tree class that uses the Red-Black algorithm.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class BinaryTree : public Tree<T> {
private:

	/**
	 * @brief A recursive function to clear all nodes from a tree
	 *
	 * Performs a postorder traversal of the tree to remove all nodes.
	 * The anchor is reached when a leaf is null.  This is called by
	 * the clear() to start from the root node of the tree.
	 *
	 * @param node a reference to the next node to search
	 */
	void clearDelegate(std::shared_ptr<Node<T>> node) {
		if (node == nullptr) {
			return;
		}

		this->clearDelegate(node->getLeft());
		this->clearDelegate(node->getRight());

		node.reset();
	}

	/**
	 * @brief Helper function to insert a node into the binary tree
	 *
	 * Recursively traverses the tree to find the appropriate position for the new node
	 * based on the comparator, then inserts it.
	 *
	 * @param data The data to be inserted
	 * @param node The current node in the recursion
	 * @param parent The parent of the current node
	 * @return Shared pointer to the inserted node or the current node in recursion
	 */
	std::shared_ptr<Node<T>> insertDelegate(T data, std::shared_ptr<Node<T>> node,
											std::shared_ptr<Node<T>> parent) {
		std::shared_ptr<Node<T>> tnode;

		if (this->_root == nullptr) {
			tnode = newNode(data, parent);
			this->_root = tnode;
			this->_front = this->_back = tnode;
			this->_size++;
			return this->_root;
		} else {
			if (node == nullptr) {
				this->_size++;
				tnode = newNode(data, parent);

				if (this->comparator(data, this->front()) < 0) {
					this->_front = tnode;
				} else if (this->comparator(data, this->back())) {
					this->_back = tnode;
				}

				return tnode;
			}

			if (this->comparator(data, node->getData()) < 0) {
				node->setLeft(insertDelegate(data, node->getLeft(), node));
			} else if (this->comparator(data, node->getData()) > 0) {
				node->setRight(insertDelegate(data, node->getRight(), node));
			}

			return node;
		}
	}

	/**
	 * @brief Fixes violations of Red-Black tree properties after insertion
	 *
	 * Rebalances the tree and recolors nodes as necessary to maintain
	 * Red-Black tree invariants after a node is inserted.
	 *
	 * @param node The newly inserted node that might cause violations
	 */
	void insertFixUp(std::shared_ptr<Node<T>> node) {
		// TODO: implement insertFixUp for red-black algorihtm
	}

	/**
	 * @brief Creates a new node with the specified data and parent
	 * @param data Data to store in the new node
	 * @param parent Parent node for the new node
	 * @return std::shared_ptr<Node<T>> Shared pointer to the newly created node
	 */
	std::shared_ptr<Node<T>> newNode(T data, std::shared_ptr<Node<T>> &parent) {
		std::shared_ptr<ds::Node<T>> node;
		NodeBuilder<T> builder;

		node = builder.withData(data).withParent(parent).asRed().build();
		return node;
	}

	/**
	 * @brief Helper function to perform post-order traversal of the tree
	 *
	 * Recursively visits left subtree, right subtree, then the node itself.
	 *
	 * @param node The current node in the traversal
	 * @param out Vector to collect the elements in post-order sequence
	 */
	void postorderDelegate(std::shared_ptr<Node<T>> node, std::vector<T> &out) {
		if (node == nullptr) {
			return;
		}

		this->postorderDelegate(node->getLeft(), out);
		this->postorderDelegate(node->getRight(), out);
		out.push_back(node->getData());
	}

	/**
	 * @brief Helper function to perform pre-order traversal of the tree
	 *
	 * Recursively visits the node itself, then left subtree, then right subtree.
	 *
	 * @param node The current node in the traversal
	 * @param out Vector to collect the elements in pre-order sequence
	 */
	void preorderDelegate(std::shared_ptr<Node<T>> node, std::vector<T> &out) {
		if (node == nullptr) {
			return;
		}

		out.push_back(node->getData());
		this->preorderDelegate(node->getLeft(), out);
		this->preorderDelegate(node->getRight(), out);
	}

public:

	BinaryTree() : Tree<T>() {}

	~BinaryTree() {
		this->clear();
	}

	/**
	 * @brief Constructor for BinaryTree that takes a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	BinaryTree(Comparator<T> comparator) : Tree<T>(comparator) {}

	T at(size_t index) {
		// TODO: implement at in BinaryTree
		T data;
		return data;
	}

	void clear() {
		this->clearDelegate(this->_root);

		this->_root.reset();
		this->_front.reset();
		this->_back.reset();
		this->_size = 0;
	}

	bool contains(T data) {
		// TODO: implements contains in BinaryTree
		return false;
	}

	Match<T> find(T data) {
		// TODO: implement find in BinaryTree
		Match<T> match;
		return match;
	}

	std::string json() const {
		// TODO: implement json in BinaryTree
		return "";
	}

	/**
	 * @brief Inserts a new element into the binary tree
	 * @param data The data to insert into the tree
	 */
	void insert(T data) {
		std::shared_ptr<Node<T>> tnode;
		tnode = this->insertDelegate(data, this->_root, nullptr);

		if (tnode == nullptr) {
			this->insertFixUp(tnode);
		}
	}

	/**
	 * @brief Performs a post-order traversal of the tree
	 *
	 * Post-order traversal visits nodes in the order: left subtree, right subtree, then root.
	 * This traversal is useful for operations where child nodes must be processed before parent
	 * nodes, such as when deleting nodes or calculating a tree's height.
	 *
	 * @return A vector containing the elements in post-order traversal sequence
	 */
	std::vector<T> postorder() {
		std::vector<T> out;
		this->postorderDelegate(this->_root, out);
		return out;
	}

	/**
	 * @brief Performs a pre-order traversal of the tree
	 *
	 * Pre-order traversal visits nodes in the order: root, left subtree, then right subtree.
	 * This traversal is useful for creating a copy of the tree or generating a prefix expression
	 * from an expression tree. It also naturally corresponds to depth-first search.
	 *
	 * @return A vector containing the elements in pre-order traversal sequence
	 */
	std::vector<T> preorder() {
		std::vector<T> out;
		this->preorderDelegate(this->_root, out);
		return out;
	}

	T removeAt(size_t index, std::shared_ptr<Node<T>> tnode) {
		// TODO: implmeent removeAt in BinaryTree
		T data;
		return data;
	}

	T removeValue(T value) {
		// TODO: implement removeValue in BinaryTree
		T data;
		return data;
	}

	std::string str() const {
		// TODO: implement str in BinaryTree
		return "";
	}
};

}  // namespace ds
