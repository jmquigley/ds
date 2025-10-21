#pragma once

#include <ds/Replicate.hpp>
#include <ds/property.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

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
class BaseIterator : public Replicate<T, BaseIterator<T, C>> {
	/// @brief an internal pointer to the object that will be iterated
	PROPERTY(lp, Lp, std::weak_ptr<C<T>>);

public:

	constexpr BaseIterator() : BaseIterator(std::weak_ptr<C<T>>()) {};

	/**
	 * @brief Constructor that initializes the iterator with a node pointer.
	 * @param lp Shared pointer to the starting node for iteration
	 */
	constexpr BaseIterator(std::weak_ptr<C<T>> lp) : _lp(lp) {}

	/**
	 * @brief Copy constructor
	 * @param iterator The source iterator to copy from
	 * @details Creates a new iterator with the same internal state as the
	 * source
	 */
	constexpr BaseIterator(const BaseIterator &iterator) {
		this->copy(iterator);
	}

	/**
	 * @brief Move constructor
	 * @param iterator The source iterator to move from
	 * @details Creates a new iterator by transferring ownership from the source
	 */
	constexpr BaseIterator(BaseIterator &&iterator) noexcept {
		this->move(std::move(iterator));
	}

	~BaseIterator() override = default;

	/**
	 * @brief Call operator to reassign the iterator to a new node by shared
	 * pointer
	 * @param other The shared pointer to the node to assign to this iterator
	 * @return Reference to this iterator after assignment
	 * @details Updates the iterator to point to the provided node pointer
	 */
	constexpr auto operator()(std::shared_ptr<C<T>> other) {
		this->_lp = other;
		return *this;
	}

	/**
	 * @brief Copy assignment operator
	 * @param iterator The source iterator to copy from
	 * @return Reference to this iterator after assignment
	 * @details Assigns this iterator's state to be the same as the source
	 */
	auto operator=(const BaseIterator &iterator) -> BaseIterator & {
		this->copy(iterator);
		return *this;
	}

	/**
	 * @brief Move assignment operator
	 * @param iterator The source iterator to move from
	 * @return Reference to this iterator after assignment
	 * @details Transfers ownership of resources from the source iterator to
	 * this one
	 */
	auto operator=(BaseIterator &&iterator) noexcept -> BaseIterator & {
		this->move(std::move(iterator));
		return *this;
	}

	/**
	 * @brief Pre-increment operator.
	 *
	 * Advances the iterator to the next node in the sequence.
	 *
	 * @return Reference to this iterator after advancing
	 */
	constexpr auto operator++() -> BaseIterator & {
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
	constexpr auto operator++(int) -> BaseIterator & {
		return this->next();
	}

	/**
	 * @brief Pre-decrement operator.
	 *
	 * Advances the iterator to the previous node in the sequence.
	 *
	 * @return Reference to this iterator after advancing
	 */
	constexpr auto operator--() -> BaseIterator & {
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
	constexpr auto operator--(int) -> BaseIterator & {
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
	constexpr auto operator==(const BaseIterator &rhs) const -> bool {
		return this->_lp.lock() == rhs._lp.lock();
	}

	/**
	 * @brief Inequality comparison operator.
	 *
	 * Determines if two iterators point to different nodes.
	 *
	 * @param rhs The right-hand side iterator to compare with
	 * @return true if the iterators point to different nodes, false otherwise
	 */
	constexpr auto operator!=(const BaseIterator &rhs) const -> bool {
		return this->_lp.lock() != rhs._lp.lock();
	}

	/**
	 * @brief Boolean conversion operator
	 * @return true if the iterator points to a valid node, false otherwise
	 * @details Checks if the weak pointer to the current node has not expired,
	 *          allowing the iterator to be used in boolean expressions to
	 * verify validity
	 */
	constexpr explicit operator bool() const {
		return !this->_lp.expired();
	}

	/**
	 * @brief Dereference operator.
	 *
	 * Retrieves the data from the node pointed to by the iterator.
	 * Returns a default-constructed value if the iterator points to nullptr.
	 *
	 * @return The data of the current node, or a default T value if no node
	 */
	auto operator*() -> T {
		if (!_lp.expired()) {
			return _lp.lock()->data();
		}

		throw std::runtime_error("Error dereferencing invalid iterator");
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
	friend auto operator<<(std::ostream &st, const BaseIterator &it)
		-> std::ostream & {
		return st << it._lp.lock();
	}

	/**
	 * @brief Creates a copy from another iterator
	 * @param other The source iterator to copy from
	 * @return Reference to this iterator after copying
	 * @details Copies the internal pointer state from the other iterator
	 */
	auto copy(const BaseIterator<T, C> &other)
		-> BaseIterator<T, C> & override {
		this->_lp = other._lp;
		return *this;
	}

	/**
	 * @brief Creates a deep copy of the iterator.
	 * @details Allocates a new iterator with the same internal state via a
	 * shared pointer
	 * @return a shared pointer to a new iterator instance
	 */
	auto deepcopy() -> std::shared_ptr<BaseIterator<T, C>> override {
		return std::make_shared<BaseIterator<T, C>>(this->_lp);
	}

	/**
	 * @brief Iterates through the linked structure applying a callback to each
	 * node
	 * @details Traverses the structure starting from the current node and
	 * moving right, invoking the callback with the node's index and a reference
	 * to the node
	 *
	 * @tparam Callback Callable type that accepts an index and a node reference
	 * @param callback Function to call for each node in the sequence
	 */
	template<typename Callback>
	auto each(Callback callback) -> void {
		std::shared_ptr<C<T>> nodeptr = _lp.lock();
		size_t index = 0;

		while (nodeptr) {
			// Invoke callback with current index and node
			callback(index++, *nodeptr);
			nodeptr = nodeptr->getRight();
		}
	}

	/**
	 * @brief retrieves a reference to the shared pointer contained in the
	 * iterator.
	 * @returns a `std::shared_ptr` to the iterators current node pointer
	 */
	auto get() -> std::shared_ptr<C<T>> {
		return _lp.lock();
	}

	/**
	 * @brief Moves resources from another iterator
	 * @param other The source iterator to move from
	 * @return Reference to this iterator after moving
	 * @details Transfers ownership of the internal pointer and resets the
	 * source
	 */
	auto move(BaseIterator<T, C> &&other) -> BaseIterator<T, C> & override {
		this->_lp = std::move(other._lp);
		other._lp.reset();
		return *this;
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
	auto next() -> BaseIterator & {
		if (this->_lp.expired()) {
			throw std::runtime_error("The iterator is expired");
		}

		auto p = this->_lp.lock();

		if (p) {
			_lp = p->getRight();
		}

		return *this;
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
	auto previous() -> BaseIterator & {
		if (this->_lp.expired()) {
			throw std::runtime_error("The iterator is expired");
		}

		auto p = this->_lp.lock();

		if (p) {
			_lp = p->getLeft();
		}

		return *this;
	}
};
}  // namespace ds
