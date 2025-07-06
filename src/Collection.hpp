#pragma once

#include <Comparator.hpp>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <property.hpp>
#include <stdexcept>

/**
 * @namespace ds
 * @brief Contains data structure related classes for a set of collection classes
 */
namespace ds {

/**
 * @brief Namespace for data structures.
 * @tparam T the data type that will be stored in the collection
 * @tparam C the BaseNode class type that will be used within the collection
 *
 */
template<typename T, template<class> class C>
class Collection {
protected:

	/**
	 * @brief Pointer to the first/front element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(_front, Front, std::weak_ptr<C<T>>, protected:);
	/**
	 * @brief Pointer to the last/back element in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(_back, Back, std::weak_ptr<C<T>>, protected:);
	/**
	 * @brief The number of elements currently in the collection.
	 * @protected
	 */
	PROPERTY_SCOPED(_size, Size, size_t, protected:);
	/**
	 * @brief Pointer to the root element of tree-like collections.
	 * @protected
	 */
	PROPERTY_SCOPED(_root, Root, std::shared_ptr<C<T>>, protected:);

protected:

	/**
	 * @brief A comparator object used for ordering elements within the collection.
	 *
	 * A default comparison object that is available to all classes that are part
	 * of the collection.
	 */
	Comparator<T> comparator;

public:

	/**
	 * @brief Default constructor for Collection.
	 * Initializes pointers to nullptr and length to 0.
	 */
	Collection() : _front(), _back(), _size(0), _root(nullptr) {}

	/**
	 * @brief Constructor for Collection that takes a custom comparator.
	 * @param comparator (`Comparator<T>`) An object used to compare elements of type T.
	 */
	Collection(Comparator<T> comparator) : Collection() {
		this->comparator = comparator;
	}

	/**
	 * @brief Virtual destructor for Collection.
	 * Ensures proper cleanup of derived classes.
	 */
	virtual ~Collection() {}

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
			if (this->comparator(r1->getData(), r2->getData()) != 0) {
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
	 * @brief retrieves the element at the end of the collection
	 * @return a `T` data element
	 * @throws std::bad_weak_ptr if the requested back pointer is not available
	 */
	T back() const {
		return this->_back.lock()->getData();
	}

	/**
	 * @brief Clears all elements from the collection, making it empty.
	 * @pure
	 */
	virtual void clear() = 0;

	/**
	 * @brief Checks a container for the existence of the given T element
	 * @param data (`T`) the data element to find within the collection
	 * @return true if found in the container, otherwise false
	 * @pure
	 */
	virtual bool contains(T data) const = 0;

	/**
	 * @brief Check if the collection is empty
	 * @return true if the colleciton is empty, otherwise false
	 */
	bool empty() const {
		return this->_size == 0;
	}

	/**
	 * @brief retrieves the element at the front of the collection
	 * @return a `T` data element
	 */
	T front() const {
		return this->_front.lock()->getData();
	}

	/**
	 * @brief returns a JSON representation of the given collection.
	 * @returns a std::string that contains a json representation of the
	 * collection
	 * @pure
	 */
	virtual std::string json() const = 0;

	/**
	 * @brief returns the size of the collection class
	 * @returns the size of the collection
	 */
	size_t size() const {
		return this->_size;
	}

	/**
	 * @brief a convenience method to get the current root pointer
	 * @returns a `std::shared_ptr<Node<T>>` that contains the current root
	 */
	inline virtual std::shared_ptr<C<T>> root() const {
		return this->_root;
	}

	/**
	 * @brief Returns a string representation of the collection's contents.
	 * @return a `std::string` A string describing the collection.
	 * @pure
	 */
	virtual std::string str() const = 0;
};
}  // namespace ds
