#pragma once

#include <cstddef>
#include <ds/Queue.hpp>
#include <ds/helpers.hpp>
#include <ds/property.hpp>
#include <limits>

namespace ds {

/**
 * @class Deque
 * @brief A double ended queue
 *
 * A deque (double-ended queue) is a data structure that allows insertion and
 * removal of elements from both ends efficiently. It combines the features of
 * stacks and queues
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class Deque : public Queue<T> {
	/// @brief The maximum size of the Deque
	PROPERTY_WITH_DEFAULT(maxSize, MaxSize, size_t,
						  = std::numeric_limits<std::size_t>::max());

private:

	/**
	 * @brief Checks the current internals for an overflow condition.
	 *
	 * An overflow occurs when the maxSize storage size will be exceeded
	 * on the next insert operation.
	 *
	 * @returns `boolean` true if in an overflow condition, otherwise false.
	 */
	bool overflow() {
		return this->_size >= this->_maxSize;
	}

	/**
	 * @brief initializes the Deque with values in an initializer list
	 * @param il (`std::initializer_list<T>`) a list of values to add
	 */
	void initializer(std::initializer_list<T> il) {
		for (auto it: il) {
			this->enqueue(it);
		}
	}

public:

	/**
	 * @brief Default constructor that initializes an empty Deque.
	 */
	constexpr Deque() : Queue<T>() {}

	/**
	 * @brief Constructor to set the maximum size of the Deque
	 * @param maxSize (`size_t`) the maximum size of the queue
	 */
	constexpr Deque(size_t maxSize) : Queue<T>(), _maxSize(maxSize) {}

	/**
	 * @brief the copy constructor for the Deque class
	 * @param dq (`Deque<T>`) the deque object to copy
	 */
	constexpr Deque(const Deque<T> &dq) : Deque() {
		List<T>::copy(dq);
	}

	/**
	 * @brief Move constructor for the Deque class
	 * @param dq The deque object to move from
	 * @details Transfers ownership of resources from the given deque to this
	 * new instance leaving the source deque in a valid but unspecified state
	 */
	constexpr Deque(const Deque<T> &&dq) noexcept : Deque() {
		List<T>::move(std::move(dq));
	}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the queue.
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	Deque(std::initializer_list<T> il) : Queue<T>() {
		this->initializer(il);
	}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the queue.
	 * @param maxSize (`size_t`) the maximum size of the queue
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	Deque(size_t maxSize, std::initializer_list<T> il)
		: Queue<T>(), _maxSize(maxSize) {
		this->initializer(il);
	}

	/**
	 * @brief Destructor that cleans up deque resources.
	 */
	~Deque() {
		Queue<T>::clear();
	}

	/**
	 * @brief equality operator for the Deque class
	 * @param dq (`Deque<T> &`) a reference to teh deque to copy
	 * @returns a reference to the this pointer for the object
	 */
	auto operator=(const Deque<T> &dq) -> Deque<T> & {
		this->_maxSize = dq._maxSize;
		Queue<T>::operator=(dq);
		return *this;
	}

	/**
	 * @brief Move assignment operator for the Deque class
	 * @param dq The deque object to move from
	 * @return A reference to this deque after assignment
	 * @details Transfers ownership of resources from the given deque to this
	 * instance, leaving the source deque in a valid but unspecified state
	 */
	auto operator=(Deque &&dq) noexcept -> Deque<T> & {
		this->_maxSize = dq._maxSize;
		Queue<T>::operator=(std::move(dq));
		return *this;
	}

	/**
	 * @brief adds a single item to the deque (enqueue)
	 * @param data (`T`) the data element to add to the deque
	 * @return a reference to the Deque
	 */
	auto operator+=(const T data) -> Deque<T> & override {
		this->enqueue(data);
		return *this;
	}

	/**
	 * @brief deletes everything from the current deque and resets it to its
	 * initialized state.
	 */
	auto clear() -> void override {
		Queue<T>::clear();
	}

	/**
	 * Adds an item to the end of the deque.  Checks for an overflow condition
	 * and acts if one is detected.
	 * @param data (``) the data item to add to the queue.
	 */
	auto enqueue(T data) -> void {
		if (overflow()) {
			Queue<T>::dequeue();
		}

		Queue<T>::enqueue(data);
	}

	/**
	 * @brief removes the last item in the deque
	 * @returns the last `T` data element in the list
	 */
	auto popBack() -> T {
		return Queue<T>::removeAt(as_integer(Position::BACK));
	}

	/**
	 * @brief removes the first item in the Deque
	 * @returns the first `T` data element in the Deque
	 */
	auto popFront() -> T {
		return Queue<T>::dequeue();
	}

	/**
	 * @brief places an item at the end of the Deque
	 * @param data (`T`) element to add to the Deque
	 */
	auto pushBack(T data) -> void {
		if (overflow()) {
			Queue<T>::dequeue();
		}

		Queue<T>::insert(data, Position::BACK);
	}

	/**
	 * @brief places an item at the end of the front of the Deque
	 * @param data (`T`) element to add to the Deque
	 */
	auto pushFront(T data) -> void {
		if (overflow()) {
			Queue<T>::dequeue();
		}

		Queue<T>::insert(data, Position::FRONT);
	}
};

}  // namespace ds
