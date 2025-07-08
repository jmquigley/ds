#pragma once

#include <BaseNodeBuilder.hpp>
#include <BaseTree.hpp>
#include <Match.hpp>
#include <Node.hpp>
#include <TreeNode.hpp>
#include <cstddef>
#include <functional>
#include <initializer_list>
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
	 * @brief Calculates the height of a subtree rooted at the given node
	 *
	 * This recursive function computes the height of a binary tree, defined as the
	 * maximum number of edges from the node to the most distant leaf node.
	 * A leaf node has a height of 0, and an empty tree (null node) has a height of -1.
	 *
	 * The algorithm works by:
	 * 1. Returning -1 if the node is null (base case)
	 * 2. Recursively finding the height of left and right subtrees
	 * 3. Taking the maximum of those heights and adding 1 for the current level
	 *
	 * Time complexity: O(n) where n is the number of nodes in the subtree
	 * Space complexity: O(h) where h is the height of the tree (for recursion stack)
	 *
	 * @param node The root of the subtree whose height is being calculated
	 * @return The height of the subtree as a signed integer (or -1 for empty trees)
	 */
	ssize_t findHeight(std::shared_ptr<TreeNode<T>> node) {
		if (node == nullptr) {
			return -1;
		}

		ssize_t heightLeft = findHeight(node->left());
		ssize_t heightRight = findHeight(node->right());

		if (heightLeft > heightRight) {
			return heightLeft + 1;
		} else {
			return heightRight + 1;
		}
	}

	/**
	 * @brief Helper function to perform in-order traversal of the tree
	 *
	 * Recursively visits left subtree, the node itself, and then the right subtree
	 *
	 * @param node The current node in the traversal
	 * @param callback a callback function that will be executed using each
	 * node as it is encountered (if defined).
	 */
	template<typename Callback>
	bool inorderDelegate(std::shared_ptr<TreeNode<T>> node, Callback callback) {
		if (!node) {
			return false;
		}

		// Process left subtree
		if (inorderDelegate(node->left(), callback)) {
			return true;
		}

		// Process current node
		if constexpr (std::is_same_v<decltype(callback(*node)), bool>) {
			if (callback(*node)) {
				return true;
			}
		} else {
			callback(*node);
		}

		// Process right subtree
		return inorderDelegate(node->right(), callback);
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

				if (this->comparator(data, this->first()) < 0) {
					this->_front = tnode;
				} else if (this->comparator(data, this->last())) {
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
	}

	/**
	 * @brief Helper function to perform post-order traversal of the tree
	 *
	 * Recursively visits left subtree, right subtree, then the node itself.
	 *
	 * @param node The current node in the traversal
	 * @param callback a callback function that will be executed using each
	 * node as it is encountered (if defined).
	 */
	template<typename Callback>
	bool postorderDelegate(std::shared_ptr<TreeNode<T>> node, Callback callback) {
		if (node == nullptr) {
			return false;
		}

		if (this->postorderDelegate(node->left(), callback)) {
			return true;
		}

		if (this->postorderDelegate(node->right(), callback)) {
			return true;
		}

		// Process current node
		if constexpr (std::is_same_v<decltype(callback(*node)), bool>) {
			return callback(*node);
		} else {
			callback(*node);
			return false;
		}
	}

	/**
	 * @brief Helper function to perform pre-order traversal of the tree
	 *
	 * Recursively visits the node itself, then left subtree, then right subtree.
	 *
	 * @param node The current node in the traversal
	 * @param callback a callback function that will be executed using each
	 * node as it is encountered (if defined).
	 */
	template<typename Callback>
	bool preorderDelegate(std::shared_ptr<TreeNode<T>> node, Callback callback) {
		if (node == nullptr) {
			return false;
		}

		// Process current node
		if constexpr (std::is_same_v<decltype(callback(*node)), bool>) {
			if (callback(*node)) {
				return true;
			}
		} else {
			callback(*node);
		}

		if (this->preorderDelegate(node->left(), callback)) {
			return true;
		}

		return this->preorderDelegate(node->right(), callback);
	}

	/**
	 * @brief Helper function to perform reverse-order traversal of the tree
	 *
	 * Recursively visits right subtree, the node itself, and then the left subtree
	 *
	 * @param node The current node in the traversal
	 * @param callback a callback function that will be executed using each
	 * node as it is encountered (if defined).
	 */
	template<typename Callback>
	bool reverseorderDelegate(std::shared_ptr<TreeNode<T>> node, Callback callback) {
		if (node == nullptr) {
			return false;
		}

		if (this->reverseorderDelegate(node->right(), callback)) {
			return true;
		}

		// Process current node
		if constexpr (std::is_same_v<decltype(callback(*node)), bool>) {
			if (callback(*node)) {
				return true;
			}
		} else {
			callback(*node);
		}

		return this->reverseorderDelegate(node->left(), callback);
	}

	/**
	 * @brief Performs a left rotation on the given node
	 *
	 * A left rotation is a local operation in a binary search tree that changes the structure
	 * without interfering with the in-order traversal order of the nodes. It's commonly
	 * used in self-balancing trees like Red-Black trees and AVL trees.
	 *
	 * The rotation takes the right child of xnode (ynode) and makes it the new root
	 * of the subtree, with xnode becoming the left child of ynode. The left child of
	 * ynode (if any) becomes the right child of xnode.
	 *
	 * @param xnode The node to rotate around, which will become the left child after rotation
	 */
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

	/**
	 * @brief Performs a right rotation on the given node
	 *
	 * A right rotation is a local operation in a binary search tree that changes the structure
	 * without interfering with the in-order traversal order of the nodes. It's commonly
	 * used in self-balancing trees like Red-Black trees and AVL trees.
	 *
	 * The rotation takes the left child of xnode (ynode) and makes it the new root
	 * of the subtree, with xnode becoming the right child of ynode. The right child of
	 * ynode (if any) becomes the left child of xnode.
	 *
	 * @param xnode The node to rotate around, which will become the right child after rotation
	 */
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

	/**
	 * @brief Constructor for BinaryTree that takes a custom comparator.
	 * @param comparator An object used to compare elements of type T.
	 */
	BinaryTree(Comparator<T> comparator) : BaseTree<T, TreeNode>(comparator) {}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the tree.
	 * @param il (`std::initializer_list`) a list of values to seed the tree
	 */
	BinaryTree(std::initializer_list<T> il) : BinaryTree<T>() {
		for (auto it: il) {
			this->insert(it);
		}
	}

	~BinaryTree() {
		this->clear();
	}

	/**
	 * @brief Iterates through the tree and saves all date elements into an array.
	 *
	 * This function follows an inorder traversal to build the list.
	 *
	 * @param out a referece to the vector that should contain each data elemetn
	 */
	void array(std::vector<T> &out) {
		inorderDelegate(this->root(), [&](TreeNode<T> &node) { out.push_back(node.getData()); });
	}

	/**
	 * @brief Iterates through the tree and saves all data elemnts into an array.
	 *
	 * This function is a wrapper around the main array method.  It will allocate
	 * a vector, fill it, and return it.  The main method is givent a vector, where
	 * this one creates the vector and returns it.
	 *
	 * @returns a `std::vector<T>` that contains all data elements in order.
	 */
	std::vector<T> array() {
		std::vector<T> out;
		array(out);
		return out;
	}

	/**
	 * @brief Retrieves the element at the specified index position in the binary tree.
	 *
	 * This method peforms an inorder or reverseorder traversal of the tree and counts
	 * the current position.  When it is encountered it will stop the traversal and
	 * return the data at that node.  This is an O(N) operation and NOT an indexed
	 * operation.  Just NOTE that this is not a fast lookup index operation.
	 *
	 * @param index (`size_t`) the index position within the tree, using inorder traversal ordering
	 * @returns the data element located at the given index
	 * @throws std::out_of_range error if an invalid index is requested
	 */
	T at(size_t index) override {
		// Boundary check
		if (index >= this->_size) {
			throw std::out_of_range("Invalid tree position index requested");
		}

		// Fast path for first element in inorder traversal
		if (index == 0 && this->_front.lock()) {
			return this->_front.lock()->getData();
		}

		// Fast path for last element in inorder traversal
		if (index == this->_size - 1 && this->_back.lock()) {
			return this->_back.lock()->getData();
		}

		T data {};
		bool found = false;

		// Choose optimal traversal direction based on which end is closer
		if (index < this->_size / 2) {
			// Use inorder traversal for indices in first half
			size_t currentPos = 0;
			inorderDelegate(this->_root, [&](TreeNode<T> &node) -> bool {
				if (currentPos == index) {
					data = node.getData();
					found = true;
					return true;  // Stop traversal
				}
				currentPos++;
				return false;  // Continue traversal
			});
		} else {
			// Use reverseorder traversal for indices in second half
			size_t currentPos = this->_size - 1;
			reverseorderDelegate(this->_root, [&](TreeNode<T> &node) -> bool {
				if (currentPos == index) {
					data = node.getData();
					found = true;
					return true;  // Stop traversal
				}
				currentPos--;
				return false;  // Continue traversal
			});
		}

		if (!found) {
			throw std::runtime_error("Element at index not found during traversal");
		}

		return data;
	}

	/**
	 * Removes all nodes from the current tree.
	 */
	void clear() {
		clearDelegate(this->_root);

		if (this->_root) {
			this->_root.reset();
		}
		this->_front.reset();
		this->_back.reset();
		this->_size = 0;
	}

	/**
	 * @brief Checks if a `T` data element exists within the binary tree
	 * @returns true if the data element exists in the list, otherwise false.
	 */
	inline bool contains(T data) const override {
		Match<T, TreeNode> match = find(data);
		return match.found();
	}

	/**
	 * @brief Searches for a node with the specified data in the binary tree
	 *
	 * This method traverses the binary tree to find a node that matches the
	 * given data according to the comparator function. If found, the Match
	 * object will contain information about the found node.
	 *
	 * @param data The value to search for
	 * @return Match object containing the result of the search
	 */
	Match<T, TreeNode> find(T data) const override {
		std::shared_ptr<TreeNode<T>> tnode = this->_root;
		Match<T, TreeNode> match;

		while (tnode != nullptr) {
			int result = this->comparator(tnode->getData(), data);

			if (result == 0) {
				match.setData(data);
				match.setFound(true);
				match.setIndex(0);
				match.setRef(tnode);
				return match;
			} else if (result < 0) {
				tnode = tnode->right();
			} else {
				tnode = tnode->left();
			}
		}

		return match;
	}

	/**
	 * @brief Calculates the height of the binary tree
	 *
	 * The height of a tree is defined as the number of edges on the longest path
	 * from the root node to any leaf node. An empty tree has a height of 0, and
	 * a tree with only a root node also has a height of 0.
	 *
	 * This method serves as a public interface that:
	 * 1. Calls the private recursive findHeight() method starting at the root
	 * 2. Transforms the result to ensure empty or invalid trees return 0 instead of -1
	 * 3. Presents a consistent height definition to external callers
	 *
	 * Time complexity: O(n) where n is the number of nodes in the tree
	 * Space complexity: O(h) where h is the height of the tree (for recursion stack)
	 *
	 * @return The height of the tree as a non-negative integer
	 */
	size_t height() override {
		ssize_t n;
		n = this->findHeight(this->root());
		return n <= 0 ? 0 : n;
	}

	/**
	 * @brief Performs an in-order traversal of the tree
	 *
	 * In-order traversal visits nodes in the order: left subtree, root, then right subtree.
	 * This traversal is useful to retrieve the data in sorted order.  As each node is
	 * encounterd it is passed to a callback function for use.
	 *
	 * @param callback a function pointer that will be executed on each node as it is
	 * encountered.
	 */
	template<typename Callback>
	bool inorder(Callback callback) {
		return this->inorderDelegate(this->_root, callback);
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

	/**
	 * @brief Performs a post-order traversal of the tree
	 *
	 * Post-order traversal visits nodes in the order: left subtree, right subtree, then root.
	 * This traversal is useful for operations where child nodes must be processed before parent
	 * nodes, such as when deleting nodes or calculating a tree's height.
	 *
	 * @param callback a function pointer that will be executed on each node as it is
	 * encountered.
	 */
	template<typename Callback>
	bool postorder(Callback callback) {
		return this->postorderDelegate(this->_root, callback);
	}

	/**
	 * @brief Performs a pre-order traversal of the tree
	 *
	 * Pre-order traversal visits nodes in the order: root, left subtree, then right subtree.
	 * This traversal is useful for creating a copy of the tree or generating a prefix expression
	 * from an expression tree. It also naturally corresponds to depth-first search.
	 *
	 * @param callback a function pointer that will be executed on each node as it is
	 * encountered.
	 */
	template<typename Callback>
	bool preorder(Callback callback) {
		return this->preorderDelegate(this->_root, callback);
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

	/**
	 * @brief Performs an reverse-order traversal of the tree
	 *
	 * Reverse-order traversal visits nodes in the order: right subtree, root,
	 * then left subtree.  This traversal is useful to retrieve the data in
	 * reverse sorted order.  As each node is encounterd it is passed to a callback
	 * function for use.
	 *
	 * @param callback a function pointer that will be executed on each node as it is
	 * encountered.
	 */
	template<typename Callback>
	bool reverseorder(Callback callback) {
		return this->reverseorderDelegate(this->_root, callback);
	}

	std::string str() const override {
		// TODO: implement str in BinaryTree
		return "";
	}
};

}  // namespace ds
