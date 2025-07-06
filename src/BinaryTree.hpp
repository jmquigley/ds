#pragma once

#include <BaseNodeBuilder.hpp>
#include <BaseTree.hpp>
#include <Match.hpp>
#include <Node.hpp>
#include <TreeNode.hpp>
#include <cstddef>
#include <limits>
#include <property.hpp>
#include <string>
#include <vector>

namespace ds {

/**
 * @class BinaryTree
 * @brief A binary tree class that uses the Red-Black algorithm.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class BinaryTree : public BaseTree<T, TreeNode> {
private:

	/**
	 * @brief a temporary node pointer value used to store the latest
	 * value inserted into the tree.
	 */
	std::weak_ptr<TreeNode<T>> _latestNode;

	/**
	 * @brief A recursive function to clear all nodes from a tree
	 *
	 * Performs a postorder traversal of the tree to remove all nodes.
	 * The anchor is reached when a leaf is null.  This is called by
	 * the clear() to start from the root node of the tree.
	 *
	 * @param node a reference to the next node to search
	 */
	void clearDelegate(std::shared_ptr<TreeNode<T>> node) {
		if (node == nullptr) {
			return;
		}

		this->clearDelegate(node->getLeft());
		this->clearDelegate(node->getRight());

		node.reset();
	}

	/**
	 * @brief Helper function to perform in-order traversal of the tree
	 *
	 * Recursively visits left subtree, the node itself, and then the right subtree
	 *
	 * @param node The current node in the traversal
	 * @param out Vector to collect the elements in in-order sequence
	 */
	void inorderDelegate(std::shared_ptr<TreeNode<T>> node, std::vector<T> &out) {
		if (node == nullptr) {
			return;
		}

		this->inorderDelegate(node->getLeft(), out);
		out.push_back(node->getData());
		this->inorderDelegate(node->getRight(), out);
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
	std::shared_ptr<TreeNode<T>> insertDelegate(T data, std::shared_ptr<TreeNode<T>> node,
												std::shared_ptr<TreeNode<T>> parent) {
		std::shared_ptr<TreeNode<T>> tnode;

		if (this->_root == nullptr) {
			// first node in the tree
			tnode = newNode(data, parent);
			this->_latestNode = tnode;
			this->_root = tnode;
			this->_front = this->_back = this->_latestNode;
			this->_size++;
			return this->_root;
		} else {
			if (node == nullptr) {
				// found a leaf, so insert in this location
				this->_size++;
				tnode = newNode(data, parent);
				this->_latestNode = tnode;

				if (this->comparator(data, this->front()) < 0) {
					this->_front = tnode;
				} else if (this->comparator(data, this->back())) {
					this->_back = tnode;
				}

				return tnode;
			}

			// recursively descend through the tree to find insertion point
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
	 * @param xnode (`std::shared_ptr<Node<T>>`) The newly inserted node that
	 * might cause violations
	 */
	void insertFixUp(std::shared_ptr<TreeNode<T>> xnode) {
		std::shared_ptr<TreeNode<T>> ynode;

		while (xnode != this->_root && xnode->parent()->isRed()) {
			if (xnode->parent() == xnode->parent()->parent()->getLeft()) {
				ynode = xnode->parent()->parent()->getRight();

				if (ynode != nullptr && ynode->isRed()) {
					xnode->parent()->setBlack();
					ynode->setBlack();
					xnode->parent()->parent()->setRed();
					xnode = xnode->parent()->parent();
				} else {
					if (xnode == xnode->parent()->getRight()) {
						xnode = xnode->parent();
						rotateLeft(xnode);
					}

					xnode->parent()->setBlack();
					xnode->parent()->parent()->setRed();
					rotateRight(xnode->parent()->parent());
				}
			} else {
				ynode = xnode->parent()->parent()->getLeft();

				if (ynode != nullptr && ynode->isRed()) {
					xnode->parent()->setBlack();
					ynode->setBlack();
					xnode->parent()->parent()->setRed();
					xnode = xnode->parent()->parent();
				} else {
					if (xnode == xnode->parent()->getLeft()) {
						xnode = xnode->parent();
						rotateRight(xnode);
					}

					xnode->parent()->setBlack();
					xnode->parent()->parent()->setRed();
					rotateLeft(xnode->parent()->parent());
				}
			}
		}

		this->_root->setBlack();
	}

	/**
	 * @brief Creates a new node with the specified data and parent
	 * @param data Data to store in the new node
	 * @param parent Parent node for the new node
	 * @return std::shared_ptr<Node<T>> Shared pointer to the newly created node
	 */
	std::shared_ptr<TreeNode<T>> newNode(T data, std::shared_ptr<TreeNode<T>> &parent) {
		std::shared_ptr<ds::TreeNode<T>> node;
		TreeNodeBuilder<T> builder;

		node = builder.withData(data).withParent(parent).asRed().build();
		return node;
		// BUG: check if this can just return node
		// return std::static_pointer_cast<TreeNode<T>>(node);
	}

	/**
	 * @brief Helper function to perform post-order traversal of the tree
	 *
	 * Recursively visits left subtree, right subtree, then the node itself.
	 *
	 * @param node The current node in the traversal
	 * @param out Vector to collect the elements in post-order sequence
	 */
	void postorderDelegate(std::shared_ptr<TreeNode<T>> node, std::vector<T> &out) {
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
	void preorderDelegate(std::shared_ptr<TreeNode<T>> node, std::vector<T> &out) {
		if (node == nullptr) {
			return;
		}

		out.push_back(node->getData());
		this->preorderDelegate(node->getLeft(), out);
		this->preorderDelegate(node->getRight(), out);
	}

	void rotateLeft(std::shared_ptr<TreeNode<T>> xnode) {
		std::shared_ptr<TreeNode<T>> ynode = xnode->getRight();

		xnode->setRight(ynode->getLeft());

		if (ynode->getLeft() != nullptr) {
			// fix y's left child parent pointer
			ynode->getLeft()->setParent(xnode);
		}

		ynode->setParent(xnode->parent());	// link x's parent to y

		if (xnode->parent() == nullptr) {
			// special case fix when rotating root
			this->_root = ynode;
		} else {
			if (xnode == xnode->parent()->getLeft()) {
				xnode->parent()->setLeft(ynode);
			} else {
				xnode->parent()->setRight(ynode);
			}
		}

		ynode->setLeft(xnode);	  // move previous x into y's left child
		xnode->setParent(ynode);  // fix the parent pointer after previous move
	}

	void rotateRight(std::shared_ptr<TreeNode<T>> xnode) {
		std::shared_ptr<TreeNode<T>> ynode = xnode->getLeft();

		// turn y's right subtree into x's left subtree
		xnode->setLeft(ynode->getRight());

		if (ynode->getRight() != nullptr) {
			// fix y's right child parent pointer
			ynode->getRight()->setParent(xnode);
		}

		ynode->setParent(xnode->parent());	// link x's parent to y

		if (xnode->parent() == nullptr) {
			// special case fix when rotation root
			this->_root = ynode;
		} else {
			if (xnode == xnode->parent()->getRight()) {
				xnode->parent()->setRight(ynode);
			} else {
				xnode->parent()->setLeft(ynode);
			}
		}

		ynode->setRight(xnode);	  // move previous x into y's right child
		xnode->setParent(ynode);  // fix y's left child parent pointer
	}

public:

	BinaryTree() : BaseTree<T, TreeNode>() {}

	~BinaryTree() {
		this->clear();
	}

	/**
	 * @brief Constructor for BinaryTree that takes a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	BinaryTree(Comparator<T> comparator) : BaseTree<T, TreeNode>(comparator) {}

	T at(size_t index) {
		// TODO: implement at in BinaryTree
		T data {};
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

	/**
	 * @brief Performs an in-order traversal of the tree
	 *
	 * In-order traversal visits nodes in the order: left subtree, root, then right subtree.
	 * This traversal is useful to retrieve the data in sorted order.
	 *
	 * @return A vector containing the elements in in-order traversal sequence
	 */
	std::vector<T> inorder() {
		std::vector<T> out;
		this->inorderDelegate(this->_root, out);
		return out;
	}

	/**
	 * @brief Inserts a new element into the binary tree
	 * @param data The data to insert into the tree
	 */
	void insert(T data) {
		std::shared_ptr<TreeNode<T>> tnode;

		std::shared_ptr<TreeNode<T>> snode;
		this->insertDelegate(data, this->_root, nullptr);

		tnode = this->_latestNode.lock();
		if (tnode != nullptr) {
			insertFixUp(tnode);
		}
	}

	std::string json() const {
		// TODO: implement json in BinaryTree
		return "";
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

	/**
	 * @brief Removes an element from the tree at the given position (based on its
	 * inorder traversal position).
	 *
	 * @param index (`size_t`) the location within the tree to remove
	 * @param tnode (`std::shared_ptr<TreeNode<T>>`) a convenience cache node from
	 * a search to help short circuit a lookup for deletion that has already occurred.
	 * @returns the value that was removed from the tree
	 */
	T removeAt(size_t index, std::shared_ptr<TreeNode<T>> tnode = nullptr) {
		// TODO: implmeent removeAt in BinaryTree
		T data {};
		return data;
	}

	T removeValue(T value) {
		// TODO: implement removeValue in BinaryTree
		T data {};
		return data;
	}

	std::string str() const {
		// TODO: implement str in BinaryTree
		return "";
	}
};

}  // namespace ds
