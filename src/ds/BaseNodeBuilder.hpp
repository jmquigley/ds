#pragma once

#include <ds/BaseBitFlag.hpp>
#include <ds/Path.hpp>
#include <ds/constants.hpp>
#include <memory>
#include <vector>

namespace ds {

/**
 * @class Node
 * @brief Forward declaration of Node class
 * @tparam T The type of data stored in the node
 */
template<typename T>
class Node;

/**
 * @class TreeNode
 * @brief Forward declaration of TreeNode class
 * @tparam T The type of data stored in the node
 */
template<typename T>
class TreeNode;

template<typename T>
class GeneralTreeNode;

/**
 * @class BaseNodeBuilder
 * @brief A base class for all builder classes such as Node and TreeNode
 *
 * Provides methods to set various properties of a Node before building the
 * final shared_ptr wrapped object, ensuring proper memory management.
 *
 * @tparam T The type of data for the Node being built
 * @tparam C The node class type (Node or TreeNode)
 * @tparam B The derived builder type for CRTP pattern
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

	/**
	 * @brief Virtual destructor for proper inheritance
	 */
	virtual ~BaseNodeBuilder() = default;

	/**
	 * @brief Sets the red flag on the node
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &asRed() {
		nodePtr->setRed();
		return derived();
	}

	/**
	 * @brief Sets the black flag on the node
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &asBlack() {
		nodePtr->setBlack();
		return derived();
	}

	/**
	 * @brief Finalizes the build process and returns the constructed Node
	 * object.
	 * @return A `std::shared_ptr<C<T>>` to the fully configured BaseNode
	 * object.
	 */
	std::shared_ptr<C<T>> build() {
		return nodePtr;
	}

	/**
	 * @brief Sets the data for the BaseNode being built.
	 * @param data (`T`) The data to set.
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &withData(T data) {
		nodePtr->setData(data);
		return derived();
	}

	/**
	 * @brief Sets the flags for the Node being built.
	 * @param flags (`ByteFlag`) the ByteFlag value to set.
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &withFlags(ByteFlag flags) {
		nodePtr->setFlags(flags);
		return derived();
	}

	/**
	 * @brief Sets the parent Node for the Node being built.
	 * @param parent (`std::shared_ptr<C<T>>`) A shared pointer to the parent
	 * BaseNode.
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &withParent(std::shared_ptr<C<T>> parent) {
		nodePtr->setParent(parent);
		return derived();
	}

	/**
	 * @brief Sets the right child Node for the Node being built.
	 * @param right (`std::shared_potr<C<T>>`) A shared pointer to the right
	 * child Node.
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &withRight(std::shared_ptr<C<T>> right) {
		nodePtr->setRight(right);
		return derived();
	}

	/**
	 * @brief Sets the left child Node for the Node being built.
	 * @param left (`std::shared_potr<C<T>>`) A shared pointer to the left child
	 * Node.
	 * @return A `B &` reference to the derived builder class for chaining.
	 */
	B &withLeft(std::shared_ptr<C<T>> left) {
		nodePtr->setLeft(left);
		return derived();
	}
};

/**
 * @class NodeBuilder
 * @brief Concrete builder implementation for Node<T>
 * @tparam T The type of data for the Node being built
 */
template<typename T>
class NodeBuilder : public BaseNodeBuilder<T, Node, NodeBuilder<T>> {
public:

	/**
	 * @brief Default constructor initializing the base builder
	 */
	NodeBuilder() : BaseNodeBuilder<T, Node, NodeBuilder<T>>() {}
};

/**
 * @class TreeNodeBuilder
 * @brief Concrete builder implementation for TreeNode<T>
 * @tparam T The type of data for the TreeNode being built
 */
template<typename T>
class TreeNodeBuilder :
	public BaseNodeBuilder<T, TreeNode, TreeNodeBuilder<T>> {
public:

	/**
	 * @brief Default constructor initializing the base builder
	 */
	TreeNodeBuilder() : BaseNodeBuilder<T, TreeNode, TreeNodeBuilder<T>>() {}
};

/**
 * @class GeneralTreeNodeBuilder
 * @brief Concrete builder implementation for GeneralTreeNode<T>
 *
 * Provides methods to construct a GeneralTreeNode with data, key, and children.
 * Uses the builder pattern for fluent interface construction.
 *
 * @tparam T The type of data for the GeneralTreeNode being built
 */
template<typename T>
class GeneralTreeNodeBuilder {
private:

	/// @brief The shared_ptr to the Node object being built.
	std::shared_ptr<GeneralTreeNode<T>> nodePtr;

public:

	/**
	 * @brief Default constructor that initializes an empty general tree node.
	 */
	GeneralTreeNodeBuilder()
		: nodePtr(std::make_shared<GeneralTreeNode<T>>()) {}

	/**
	 * @brief Finalizes the build process and returns the constructed
	 * GeneralTreeNode object.
	 * @return A `std::shared_ptr<GeneralTreeNode<T>>` to the fully configured
	 * GeneralTreeNode object.
	 */
	std::shared_ptr<GeneralTreeNode<T>> &build() {
		return nodePtr;
	}

	/**
	 * @brief Adds a child node with the specified key and data.
	 * @param key (`std::string`) The key to identify the child node.
	 * @param data (`T`) The data for the child node.
	 * @param path (`std::string`) the path to root for this child record
	 * @return A reference to this builder for method chaining.
	 */
	GeneralTreeNodeBuilder<T> &withChild(std::string key, T data,
										 std::string path) {
		nodePtr->addChild(key, data, path);
		return *this;
	}

	/**
	 * @brief Sets the data for the GeneralTreeNode being built.
	 * @param data (`T`) The data to set.
	 * @return A reference to this builder for method chaining.
	 */
	GeneralTreeNodeBuilder<T> &withData(T data) {
		nodePtr->setData(data);
		return *this;
	}

	/**
	 * @brief Sets the key for the GeneralTreeNode being built.
	 * @param key (`std::string`) The key to identify this node.
	 * @return A reference to this builder for method chaining.
	 */
	GeneralTreeNodeBuilder<T> &withKey(std::string key) {
		return withKey(key, key);
	}

	/**
	 * @brief Sets the key for the GeneralTreeNode being built.
	 * @param key (`std::string`) The key to identify this node.
	 * @param path (`std::string`) The path associated with this key.
	 * @return A reference to this builder for method chaining.
	 */
	GeneralTreeNodeBuilder<T> &withKey(std::string key, std::string path) {
		nodePtr->setKey(key);
		nodePtr->setPath(Path(key));
		return *this;
	}

	/**
	 * @brief Sets the parent for this GeneralTreeNode being built.
	 * @param parent (`std::shared_ptr<GeneralTreeNode<T>>`) the parent for this
	 * node.
	 * @return A reference to this builder for method chaining.
	 */
	GeneralTreeNodeBuilder<T> &withParent(
		std::shared_ptr<GeneralTreeNode<T>> parent) {
		nodePtr->setParent(parent);
		return *this;
	}

	/**
	 * @brief Sets the path value for this GeneralTreeNode
	 * @param path (`std::string`) the path to set for this node
	 * @return A reference to this builder for method chaining.
	 */
	GeneralTreeNodeBuilder<T> &withPath(std::string path) {
		nodePtr->setPath(Path(path));
		return *this;
	}
};

}  // namespace ds
