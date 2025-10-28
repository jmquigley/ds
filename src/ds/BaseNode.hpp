#pragma once

#include <compare>
#include <ds/BaseBitFlag.hpp>
#include <ds/BaseNodeBuilder.hpp>
#include <ds/Replicate.hpp>
#include <ds/helpers.hpp>
#include <ds/property.hpp>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

namespace ds {

/**
 * @enum NodeFlag
 * @brief Bit flags for node properties used in tree data structures.
 *
 * Defines flags that can be set on nodes to determine their characteristics.
 * Implemented using bit positions for memory-efficient storage of boolean
 * properties.
 */
enum class NodeFlag : BYTE {
	Color = 1 << 0,	 // 0 = RED, 1 = BLACK
};

/**
 * @enum NodeColor
 * @brief Represents colors used in Red-Black tree nodes.
 *
 * In a Red-Black tree:
 * - Red nodes provide flexibility during insertions and deletions
 * - Black nodes maintain the critical "black height" property
 * - The color of nodes helps enforce the tree's balance constraints:
 *   1. Every node is either red or black
 *   2. The root is black
 *   3. All leaves (NIL nodes) are black
 *   4. If a node is red, both its children are black
 *   5. Every path from root to leaf contains the same number of black nodes
 */
enum class NodeColor { Red = 0, Black = 1 };

/**
 * @class BaseNode
 * @brief A generic node class template for tree-like data structures.
 *
 * This class represents a single node in a tree, capable of holding generic
 * data, a unique identifier, and references to left, and right child nodes. It
 * uses the PROPERTY macro for automatic getter/setter generation.
 *
 * @tparam T The type of data stored within the node.
 */
template<typename T, template<class> class C>
// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class BaseNode : private Replicate<T, C<T>> {
	/// @brief The data payload of the node.
	PROPERTY_SCOPED_WITH_DEFAULT_NO_CONST(data, Data, T, protected:, {});

	/// @brief flags used to determine bit properties in a node
	PROPERTY_SCOPED_WITH_DEFAULT_NO_CONST(flags, Flags, ByteFlag, protected:,
										  {0});

	/// @brief A shared pointer to the left child node.
	PROPERTY_SCOPED(left, Left, std::shared_ptr<C<T>>, protected:);

	/// @brief A shared pointer to the right child node.
	PROPERTY_SCOPED(right, Right, std::shared_ptr<C<T>>, protected:);

public:

	/**
	 * @brief Default constructor for Node.
	 *
	 * Initializes the flags, and left, and right to nullptr,
	 */
	constexpr BaseNode() : _left(nullptr), _right(nullptr) {}

	/**
	 * @brief Constructor for Node with initial data.
	 *
	 * Calls the main constructor with left, and right as nullptr.
	 * @param data The data to be stored in the node.
	 */
	constexpr BaseNode(T data) : BaseNode(nullptr, nullptr, ByteFlag(), data) {}

	/**
	 * @brief Full constructor for Node.
	 *
	 * Initializes left, right, and data.
	 *
	 * @param left A pointer to the left child node. Can be nullptr.
	 * @param right A pointer to the right child node. Can be nullptr.
	 * @param data The data to be stored in the node.
	 */
	constexpr BaseNode(std::shared_ptr<C<T>> left, std::shared_ptr<C<T>> right,
					   T data)
		: BaseNode(left, right, ByteFlag(), data) {}

	/**
	 * @brief Full constructor for Node.
	 *
	 * Initializes left, right, and data.
	 *
	 * @param left A pointer to the left child node. Can be nullptr.
	 * @param right A pointer to the right child node. Can be nullptr.
	 * @param flags initial internal flag settings for the new node
	 * @param data The data to be stored in the node.
	 */
	constexpr BaseNode(std::shared_ptr<C<T>> left, std::shared_ptr<C<T>> right,
					   ByteFlag flags, T data)
		: _data(data),
		  _flags(std::move(flags)),
		  _left(std::move(left)),
		  _right(std::move(right)) {}

	/**
	 * @brief Copy constructor for Node.
	 *
	 * Creates a new node by transferring ownership of resources from another
	 * node. The source node will be left in a valid but unspecified state after
	 * the move.
	 *
	 * @param other The source Node object to move resources from
	 */
	constexpr BaseNode(const C<T> &other) {
		this->copy(other);
	}

	/**
	 * @brief Move constructor for Node.
	 *
	 * Efficiently transfers ownership of resources from the source node to this
	 * node.
	 * - Preserves the generated ID of the moved-from node
	 * - Transfers data and relationship pointers
	 *
	 * @param other (`Node<T>`) The Node object to move from (will be left in a
	 * valid but unspecified state)
	 */
	constexpr BaseNode(C<T> &&other) noexcept {
		this->move(std::move(other));
	}

	/**
	 * @brief Destructor for Node.
	 */
	virtual ~BaseNode() {
		this->clear();
	}

	/**
	 * @brief Spaceship operator for the BaseNode
	 * @param other (`BaseNode &`) the other object to compare
	 * @return an ordering class for the comparison
	 */
	std::strong_ordering operator<=>(const BaseNode &other) const {
		std::strong_ordering order = std::strong_ordering::greater;

		if (this->_data < other.constData()) {
			order = std::strong_ordering::less;
		} else if (this->_data == other.constData()) {
			order = std::strong_ordering::equal;
		}

		return order;
	}

	/**
	 * @brief Checks if the data of two given nodes are equal
	 * @param other (`BaseNode &`) the node to compare against
	 * @return true if both nodes have the same data, otherwise false
	 */
	constexpr auto operator==(const BaseNode &other) const noexcept -> bool {
		return this->_data == other.constData();
	}

	/**
	 * @brief Checks if the data of two given nodes are not equal
	 * @param other (`BaseNode &`) the node to compare against
	 * @return true if both nodes do not have the same data, otherwise false
	 */
	constexpr auto operator!=(const BaseNode &other) const noexcept -> bool {
		return this->_data != other.constData();
	}

	/**
	 * @brief Overloads the stream insertion operator for Node objects.
	 *
	 * Allows printing a Node object directly to an output stream,
	 * using its `str()` method for representation.
	 * @param st The output stream.
	 * @param node The Node object to print.
	 * @return A reference to the output stream.
	 */
	friend auto operator<<(std::ostream &st, const C<T> &node)
		-> std::ostream & {
		return st << node.str();
	}

	/**
	 * @brief Copy assignment operator.
	 *
	 * Assigns the contents of another node to this node using copying.
	 * This operator creates a new deep copy of the right-hand side node,
	 * maintaining the unique identity of this node while adopting all data
	 * and relationships from the source node.
	 *
	 * @param other The right-hand side Node object to copy from
	 * @return Reference to this node after the assignment
	 */
	auto operator=(const C<T> &other) -> BaseNode & {
		this->copy(other);
		return *this;
	}

	/**
	 * @brief Move assignment operator.
	 *
	 * Transfers ownership of all resources from the right-hand side node to
	 * this node. This is more efficient than copy assignment as it avoids deep
	 * copying by moving resources from the source node, leaving it in a valid
	 * but unspecified state.
	 *
	 * @param other The right-hand side Node object to move resources from
	 * @return Reference to this node after the assignment
	 */
	auto operator=(C<T> &&other) noexcept -> BaseNode & {
		this->move(std::move(other));
		return *this;
	}

	/**
	 * @brief When dereferencing a node this operator will return the data in
	 * the node
	 * @returns The `T` data that is associated with this node.
	 */
	auto operator*() -> T & {
		return this->_data;
	}

	/**
	 * @brief Function call operator for BaseNode objects
	 * @param other (`const C<T> &`) The parameter passed to this function call
	 * operator
	 * @return a reference to this object
	 */
	auto operator()(const C<T> &other) -> BaseNode & {
		return operator=(other);
	}

	/**
	 * @brief Clears the node's identifiers and pointers, then re-initializes a
	 * new ID.
	 *
	 * Sets right, left to nullptr,
	 */
	auto clear() noexcept -> void {
		this->_data = {};
		this->_right.reset();
		this->_left.reset();
	}

	/**
	 * @brief Copies contents from another node
	 * @param other The source node to copy from
	 * @return C<T>& Reference to this node after copying
	 */
	auto copy(const C<T> &other) -> C<T> & override {
		if (this != &other) {
			this->_data = other._data;
			this->_right = other._right;
			this->_left = other._left;
			this->_flags = other._flags;
		}
		return *static_cast<C<T> *>(this);
	}

	/**
	 * @brief Creates a deep copy of the node and its subtree
	 * @return std::shared_ptr<C<T>> A shared pointer to the new copy
	 */
	auto deepcopy() -> std::shared_ptr<C<T>> override {
		// Create a shared_ptr to a new node copy
		auto copy = std::make_shared<C<T>>(this->_data);

		// Deep copy left subtree if it exists
		if (this->_left) {
			copy->_left = this->_left->deepcopy();
		}

		// Deep copy right subtree if it exists
		if (this->_right) {
			copy->_right = this->_right->deepcopy();
		}

		// Copy flags
		copy->_flags = this->_flags;

		return copy;
	}

	/**
	 * @brief Returns the current color enumeration setting for this node
	 * @returns a `NodeColor` enum reference to Red or Black
	 */
	constexpr auto getColor() noexcept -> NodeColor {
		return this->isRed() ? NodeColor::Red : NodeColor::Black;
	}

	/**
	 * Checks if this node is black.
	 * @return true if the node is black, false otherwise
	 */
	constexpr auto isBlack() const noexcept -> bool {
		return _flags.at(0) == 1;
	}

	/**
	 * Checks if this node is red.
	 * @return true if the node is red, false otherwise
	 */
	constexpr auto isRed() const noexcept -> bool {
		return _flags.at(0) == 0;
	}

	/**
	 * @brief Moves contents from another node
	 * @param other The source node to move from
	 * @return C<T>& Reference to this node after moving
	 */
	auto move(C<T> &&other) noexcept -> C<T> & override {
		if (this != &other) {
			this->_data = std::move(other._data);
			this->_right = std::move(other._right);
			this->_left = std::move(other._left);
			this->_flags = std::move(other._flags);

			// Reset the moved-from node
			other._data = {};
			other._flags = 0;
			other._left = nullptr;
			other._right = nullptr;
		}
		return *static_cast<C<T> *>(this);
	}

	/**
	 * @brief Convenience function for setting the color of a node based on
	 * the given enum.
	 *
	 * This function is a thin wrapper around the setRed/setBlack methods
	 * using an enum class named NodeColor.  There are times where the
	 * individual colors are needed (to be passed around).
	 *
	 * @param color (`NodeColor`) the color value to set.
	 */
	auto setColor(NodeColor color) -> void {
		if (color == NodeColor::Red) {
			this->setRed();
		} else {
			this->setBlack();
		}
	}

	/**
	 * Sets this node's color to black.
	 * In the Red-Black tree, black is represented by setting the Color flag.
	 */
	auto setBlack() -> void {
		this->_flags.set(static_cast<BYTE>(NodeFlag::Color));
	}

	/**
	 * Sets this node's color to red.
	 * In the Red-Black tree, red is represented by unsetting the Color flag.
	 */
	auto setRed() -> void {
		this->_flags.unset(static_cast<BYTE>(NodeFlag::Color));
	}

	/**
	 * @brief Returns a string representation of the node.
	 *
	 * Currently, it formats the node's data into a simple JSON-like string.
	 * @return A string representing the node's content.
	 */
	auto str() const -> std::string {
		std::stringstream ss;

		ss << "{";
		ss << std::quoted("data") << ":" << _data << ",";

		if (this->isRed()) {
			ss << std::quoted("color") << ":" << std::quoted("red");
		} else {
			ss << std::quoted("color") << ":" << std::quoted("black");
		}
		ss << "}";

		return ss.str();
	}
};

}  // namespace ds
