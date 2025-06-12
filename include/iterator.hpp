/**
 * @file iterator.hpp
 * @brief Defines a base class iterator for all collection classes
 */

#pragma once

#include <memory>

#include "node.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class IteratorBase
 * @brief A base iterator class for traversing node-based data structures.
 *
 * This template class provides basic iterator functionality for traversing
 * nodes in a linked structure, supporting operations like increment, comparison,
 * and dereferencing.
 *
 * @tparam T The type of data stored in the nodes being iterated
 */
template<typename T>
class IteratorBase {
	PROPERTY(lp, Lp, std::weak_ptr<Node<T>>);

public:

	IteratorBase() : IteratorBase(std::weak_ptr<Node<T>>()) {};

	/**
	 * @brief Constructor that initializes the iterator with a node pointer.
	 *
	 * @param lp Shared pointer to the starting node for iteration
	 */
	IteratorBase(std::weak_ptr<Node<T>> lp) : lp(lp) {}

	~IteratorBase() {
		if (lp.lock()) {
			lp.reset();
		}
	}

	/**
	 * @brief Pre-increment operator.
	 *
	 * Advances the iterator to the next node in the sequence.
	 *
	 * @return Reference to this iterator after advancing
	 */
	IteratorBase &operator++() {
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
	IteratorBase &operator++(int) {
		return this->next();
	}

	/**
	 * @brief Equality comparison operator.
	 *
	 * Determines if two iterators point to the same node.
	 *
	 * @param rhs The right-hand side iterator to compare with
	 * @return true if both iterators point to the same node, false otherwise
	 */
	bool operator==(const IteratorBase &rhs) const {
		auto p = this->lp.lock();
		auto rp = rhs.lp.lock();

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
	bool operator!=(const IteratorBase &rhs) const {
		auto p = this->lp.lock();
		auto rp = rhs.lp.lock();

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
		T nil = 0;

		if (!lp.expired()) {
			return lp.lock()->getData();
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
	friend std::ostream &operator<<(std::ostream &st, const IteratorBase &it) {
		return st << it.lp.lock();
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
	IteratorBase &next() {
		auto p = this->lp.lock();

		if (p) {
			lp = p->getRight();
		}

		return *this;
	}
};
}  // namespace ds
