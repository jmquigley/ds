#pragma once

#include <cstddef>
#include <cstdlib>
#include <ds/Collectable.hpp>
#include <ds/property.hpp>
#include <limits>
#include <memory>

namespace ds {

/**
 * @enum Position
 * @brief Specifies the position for operations in collections
 *
 * This enumeration provides constants to indicate specific positions
 * within a collection. Used in insertion, removal, and other position-based
 * operations to specify where in the collection the operation should occur.
 *
 * @par Example usage:
 * @code{.cpp}
 * list.insert(data, Position::BACK); // Insert at the end
 * list.insert(data, Position::FRONT); // Insert at the beginning
 * @endcode
 */
enum class Position : size_t {
	FRONT = 0,
	BACK = std::numeric_limits<std::size_t>::max()
};

/**
 * @class Collection
 * @brief Abstract base class for various collection data structures
 *
 * The Collection class serves as a foundation for implementing various
 * collection data structures such as lists, stacks, queues, etc. It defines
 * common operations that all collections should support, and maintains
 * basic collection properties like size and boundaries.
 *
 * Derived classes must implement all pure virtual methods and should properly
 * maintain the protected members (_size, _root, _front, _back) according to
 * the specific collection semantics.
 *
 * @tparam T The type of elements stored in the collection
 * @tparam N The node type used by the collection (defaults to Node<T>),
 *           must have the same interface as Node<T>
 *
 * @note The default Node type provides a basic linked structure implementation.
 *       Custom node types can be used by specifying a different template
 * parameter N.
 *
 * @par Example usage:
 * @code{.cpp}
 * // Creating a custom list that inherits from Collection
 * template<typename T>
 * class MyList : public Collection<T> {
 *     // Implementation of all required virtual methods
 * };
 * @endcode
 *
 * NOLINTBEGIN(cppcoreguidelines-special-member-functions)
 *
 */
template<typename T, template<class> class C>
class Collection : public Collectable<T> {
protected:

	/**
	 * @brief Pointer to the first/front element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(front, Front, std::weak_ptr<C<T>>, protected:);
	/**
	 * @brief Pointer to the last/back element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(back, Back, std::weak_ptr<C<T>>, protected:);
	/**
	 * @brief The number of elements currently in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(size, Size, size_t, protected:);
	/**
	 * @brief Pointer to the root element of tree-like collections.
	 * @protected
	 */
	PROPERTY_SCOPED(root, Root, std::shared_ptr<C<T>>, protected:);

public:

	/**
	 * @brief Default constructor for Collection.
	 * Initializes pointers to nullptr and length to 0.
	 */
	Collection() : _front(), _back(), _size(0), _root(nullptr) {}

	/**
	 * @brief Virtual destructor for Collection.
	 * Ensures proper cleanup of derived classes.
	 */
	virtual ~Collection() = default;

	/**
	 * @brief Array subscript operator for accessing elements by index.
	 * @param index The index of the element to access
	 * @return T The element at the specified index
	 */
	T &operator[](size_t index) {
		return this->at(index);
	}

	/**
	 * @brief adds a single item to the collection
	 * @param data (`T`) the data element to add to the collection
	 * @return a reference to the collection
	 */
	virtual Collection<T, C> &operator+=(const T data) {
		this->insert(data);
		return *this;
	}

	/**
	 * @brief Checks if the contents of two given collections are equal
	 * @param col (`Collection<T, C>`) the collection to compare against
	 * @return true if both collections have the same values, otherwise false
	 */
	bool operator==(const Collection<T, C> &col) const {
		if (this->_size != col.size()) {
			return false;
		}

		std::shared_ptr<C<T>> r1 = this->_root;
		std::shared_ptr<C<T>> r2 = col.getRoot();

		while (r1 && r2) {
			if (r1->getData() != r2->getData()) {
				return false;
			}

			r1 = r1->getRight();
			r2 = r2->getRight();
		}

		return true;
	}

	/**
	 * @brief Checks if the contents of two given collections are not equal
	 * @param col (`Collection<T,C> &`) the list to compare against
	 * @return false if both lists have the same values, otherwise true
	 */
	bool operator!=(const Collection<T, C> &col) const {
		return !operator==(col);
	}

	/**
	 * @brief Operator to clear the buffer.
	 *
	 * This is a convenience wrapper for the `clear` function, resetting the
	 * container's size to zero.
	 *
	 * @return A reference to the current object (`*this`).
	 */
	Collection<T, C> &operator~() {
		this->clear();
		return *this;
	}

	/**
	 * @brief Check if the collection is empty
	 * @return true if the colleciton is empty, otherwise false
	 */
	virtual bool empty() const {
		return this->_size == 0;
	}

	/**
	 * @brief returns a JSON representation of the given collection.
	 * @returns a std::string that contains a json representation of the
	 * collection
	 * @pure
	 */
	virtual std::string json() const {
		return this->str();
	}

	/**
	 * @brief retrieves the element at the end of the collection
	 * @return a `T` data element
	 * @throws std::bad_weak_ptr if the requested back pointer is not available
	 */
	virtual T maximum() const {
		return this->_back.lock()->getData();
	}

	/**
	 * @brief retrieves the element at the front of the collection
	 * @return a `T` data element
	 */
	virtual T minimum() const {
		return this->_front.lock()->getData();
	}
};

// NOLINTEND(cppcoreguidelines-special-member-functions)

}  // namespace ds
