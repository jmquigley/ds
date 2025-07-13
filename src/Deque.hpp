#pragma once

#include <Queue.hpp>
#include <cstddef>
#include <helpers.hpp>
#include <limits>
#include <property.hpp>
#include <vector>

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
	inline bool overflow() {
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
	Deque() : Queue<T>() {}

	/**
	 * @brief Constructor to set the maximum size of the Deque
	 * @param maxSize (`size_t`) the maximum size of the queue
	 */
	Deque(size_t maxSize) : Queue<T>(), _maxSize(maxSize) {}

	/**
	 * @brief the copy constructor for the Deque class
	 * @param dq (`Deque<T>`) the deque object to copy
	 */
	Deque(Deque<T> &dq) : Deque() {
		this->operator=(dq);
	}

	/**
	 * @brief Constructor that initializes a deque with a custom comparator.
	 * @param comparator The comparator function to use for element comparison
	 */
	Deque(Comparator<T> &comparator) : Queue<T>(comparator) {}

	/**
	 * @brief Constructor that initializes a deque with a custom comparator.
	 * and sets a default size
	 * @param maxSize (`size_t`) the maximum size of the queue
	 * @param comparator The comparator function to use for element comparison
	 */
	Deque(size_t maxSize, Comparator<T> comparator)
		: Queue<T>(comparator), _maxSize(maxSize) {}

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
	Deque<T> &operator=(Deque<T> &dq) {
		this->_maxSize = dq._maxSize;
		Queue<T>::operator=(dq);
		return *this;
	}

	/**
	 * @brief adds a single item to the deque (enqueue)
	 * @param data (`T`) the data element to add to the deque
	 * @return a reference to the Deque
	 */
	Deque<T> &operator+=(const T data) {
		this->enqueue(data);
		return *this;
	}

	/**
	 * @brief deletes everything from the current deque and resets it to its
	 * initialized state.
	 */
	inline void clear() {
		Queue<T>::clear();
	}

	/**
	 * Adds an item to the end of the deque.  Checks for an overflow condition
	 * and acts if one is detected.
	 * @param data (``) the data item to add to the queue.
	 */
	void enqueue(T data) {
		if (overflow()) {
			Queue<T>::dequeue();
		}

		Queue<T>::enqueue(data);
	}

	/**
	 * @brief removes the last item in the deque
	 * @returns the last `T` data element in the list
	 */
	T popBack() {
		return Queue<T>::removeAt(as_integer(Position::BACK));
	}

	/**
	 * @brief removes the first item in the Deque
	 * @returns the first `T` data element in the Deque
	 */
	T popFront() {
		return Queue<T>::dequeue();
	}

	/**
	 * @brief places an item at the end of the Deque
	 * @param data (`T`) element to add to the Deque
	 */
	void pushBack(T data) {
		if (overflow()) {
			Queue<T>::dequeue();
		}

		Queue<T>::insert(data, Position::BACK);
	}

	/**
	 * @brief places an item at the end of the front of the Deque
	 * @param data (`T`) element to add to the Deque
	 */
	void pushFront(T data) {
		if (overflow()) {
			Queue<T>::dequeue();
		}

		Queue<T>::insert(data, Position::FRONT);
	}
};

}  // namespace ds
