#pragma once

#include <ds/property.hpp>
#include <memory>

namespace ds {

/**
 * @class BaseIterator
 * @brief A base iterator class for traversing node-based data structures.
 *
 * This template class provides basic iterator functionality for traversing
 * nodes in a linked structure, supporting operations like increment,
 * comparison, and dereferencing.
 *
 * @tparam T The type of data stored in the nodes being iterated
 */
template<typename T, template<class> class C>
class BaseIterator {
	/// @brief an internal pointer to the object that will be iterated
	PROPERTY(lp, Lp, std::weak_ptr<C<T>>);

public:

	BaseIterator() : BaseIterator(std::weak_ptr<C<T>>()) {};

	/**
	 * @brief Constructor that initializes the iterator with a node pointer.
	 * @param lp Shared pointer to the starting node for iteration
	 */
	BaseIterator(std::weak_ptr<C<T>> lp) : _lp(lp) {}

	~BaseIterator() {
		if (_lp.lock()) {
			_lp.reset();
		}
	}

	/**
	 * @brief Pre-increment operator.
	 *
	 * Advances the iterator to the next node in the sequence.
	 *
	 * @return Reference to this iterator after advancing
	 */
	BaseIterator &operator++() {
		return this->next();
	}

	/**
	 * @brief Post-increment operator.
	 *
	 * Advances the iterator to the next node in the sequence.
	 * Note: This implementation currently behaves like pre-increment.
	 *
	 * @return Reference to this iterator after advancing
	 */
	BaseIterator &operator++(int) {
		return this->next();
	}

	/**
	 * @brief Pre-decrement operator.
	 *
	 * Advances the iterator to the previous node in the sequence.
	 *
	 * @return Reference to this iterator after advancing
	 */
	BaseIterator &operator--() {
		return this->previous();
	}

	/**
	 * @brief Post-decrement operator.
	 *
	 * Advances teh iterator to the previous node in the sequence.
	 * Note: This implementation currently behaves like the pre-decrement
	 *
	 * @return Reference to this iterator after advancing
	 */
	BaseIterator &operator--(int) {
		return this->previous();
	}

	/**
	 * @brief Equality comparison operator.
	 *
	 * Determines if two iterators point to the same node.
	 *
	 * @param rhs The right-hand side iterator to compare with
	 * @return true if both iterators point to the same node, false otherwise
	 */
	bool operator==(const BaseIterator &rhs) const {
		auto p = this->_lp.lock();
		auto rp = rhs._lp.lock();

		return p == rp;
	}

	/**
	 * @brief Inequality comparison operator.
	 *
	 * Determines if two iterators point to different nodes.
	 *
	 * @param rhs The right-hand side iterator to compare with
	 * @return true if the iterators point to different nodes, false otherwise
	 */
	bool operator!=(const BaseIterator &rhs) const {
		auto p = this->_lp.lock();
		auto rp = rhs._lp.lock();

		return p != rp;
	}

	/**
	 * @brief Dereference operator.
	 *
	 * Retrieves the data from the node pointed to by the iterator.
	 * Returns a default-constructed value if the iterator points to nullptr.
	 *
	 * @return The data of the current node, or a default T value if no node
	 */
	T operator*() const {
		T nil {};

		if (!_lp.expired()) {
			return _lp.lock()->getData();
		}

		return nil;
	}

	/**
	 * @brief Stream insertion operator.
	 *
	 * Outputs a string representation of the iterator to an output stream.
	 *
	 * @param st The output stream to write to
	 * @param it The iterator to output
	 * @return Reference to the output stream after writing
	 */
	friend std::ostream &operator<<(std::ostream &st, const BaseIterator &it) {
		return st << it._lp.lock();
	}

	/**
	 * @brief Advances the iterator to the next node.
	 *
	 * Moves the iterator forward by making it point to the right child
	 * of the current node. If the current node is nullptr, this operation
	 * has no effect.
	 *
	 * @return Reference to this iterator after advancing
	 */
	BaseIterator &next() {
		auto p = this->_lp.lock();

		if (p) {
			_lp = p->getRight();
		}

		return *this;
	}

	/**
	 * @brief retrieves a reference to the shared pointer contained in the
	 * iterator.
	 * @returns a `std::shared_ptr` to the iterators current node pointer
	 */
	std::shared_ptr<C<T>> get() {
		return _lp.lock();
	}

	/**
	 * @brief Advances the iterator to the previous node.
	 *
	 * Moves the iterator in the reverse direction backward by making it point
	 * to the left child of the current node.  If the current node is nullptr,
	 * this operation has no effect.
	 *
	 * @return Reference to this iterator after advancing
	 */
	BaseIterator &previous() {
		auto p = this->_lp.lock();

		if (p) {
			_lp = p->getLeft();
		}

		return *this;
	}
};
}  // namespace ds
