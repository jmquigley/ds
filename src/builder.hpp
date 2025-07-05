#pragma once

#include <memory>
#include <vector>

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Node
 * @brief Forward declaration of Node class
 */
template<typename T>
class Node;

/**
 * @class TreeNode
 * @brief Forward declaration of TreeNode class
 */
template<typename T>
class TreeNode;

/**
 * @class BaseNodeBuilder
 * @brief A base class for all builder classes such as Node and TreeNode
 *
 * Provides methods to set various properties of a Node before building the final
 * shared_ptr wrapped object, ensuring proper memory management.
 *
 * @tparam T The type of data for the Node being built.
 */
template<typename T, template<class> class C, typename B>
class BaseNodeBuilder {
protected:

	/// @brief The shared_ptr to the Node object being built.
	std::shared_ptr<C<T>> nodePtr;

	/// @brief Helper to cast to the derived builder type
	inline B &derived() {
		return *static_cast<B *>(this);
	}

public:

	/**
	 * @brief Default constructor that initializes an empty node.
	 */
	BaseNodeBuilder() : nodePtr(std::make_shared<C<T>>()) {}

	virtual ~BaseNodeBuilder() = default;

	/**
	 * @brief Sets the red flag on the node
	 * @return A reference to the `B` class for chaining.
	 */
	B &asRed() {
		nodePtr->setRed();
		return derived();
	}

	/**
	 * @brief Sets the black flag on the node
	 * @return A reference to the `B` class for chaining.
	 */
	B &asBlack() {
		nodePtr->setBlack();
		return derived();
	}

	/**
	 * @brief Finalizes the build process and returns the constructed Node object.
	 * @return A shared_ptr to the fully configured Node object.
	 */
	std::shared_ptr<C<T>> build() {
		return nodePtr;
	}

	/**
	 * @brief Sets the data for the Node being built.
	 * @param data The data to set.
	 * @return A reference to the `B` class for chaining.
	 */
	B &withData(T data) {
		nodePtr->setData(data);
		return derived();
	}

	/**
	 * @brief Sets the flags for the Node being built.
	 * @param flags (`ByteFlag``) the flag value to set.
	 * @return A reference to the `B` class for chaining.
	 */
	B &withFlags(ByteFlag flags) {
		nodePtr->setFlags(flags);
		return derived();
	}

	/**
	 * @brief Sets the parent Node for the Node being built.
	 * @param parent A shared pointer to the parent Node.
	 * @return A reference to the `B` class for chaining.
	 */
	B &withParent(std::shared_ptr<C<T>> parent) {
		// nodePtr->setParent(std::static_pointer_cast<Node<T>>(parent));
		nodePtr->setParent(parent);
		return derived();
	}

	/**
	 * @brief Sets the right child Node for the Node being built.
	 * @param right A shared pointer to the right child Node.
	 * @return A reference to the `B` class for chaining.
	 */
	B &withRight(std::shared_ptr<C<T>> right) {
		nodePtr->setRight(right);
		return derived();
	}

	/**
	 * @brief Sets the left child Node for the Node being built.
	 * @param left A shared pointer to the left child Node.
	 * @return A reference to the `B` class for chaining.
	 */
	B &withLeft(std::shared_ptr<C<T>> left) {
		nodePtr->setLeft(left);
		return derived();
	}
};

/**
 * @class NodeBuilder
 * @brief Concrete builder implementation for Node<T>
 */
template<typename T>
class NodeBuilder : public BaseNodeBuilder<T, Node, NodeBuilder<T>> {
public:

	NodeBuilder() : BaseNodeBuilder<T, Node, NodeBuilder<T>>() {}
};

/**
 * @class TreeNodeBuilder
 * @brief Concreete builder implementaiton for a TreeNode<T>
 */
template<typename T>
class TreeNodeBuilder : public BaseNodeBuilder<T, TreeNode, TreeNodeBuilder<T>> {
public:

	TreeNodeBuilder() : BaseNodeBuilder<T, TreeNode, TreeNodeBuilder<T>>() {}

	/**
	 * @brief Sets the child array to an inital vector of elements
	 * @param children (`std::vector<T>`) a reference to a child object vector
	 * @return A reference to the `TreeNodeBuilder` class for chaining.
	 */
	TreeNodeBuilder &withChildren(std::vector<T> &children) {
		this->nodePtr->setChildren(children);
		return *this;
	}
};

}  // namespace ds
