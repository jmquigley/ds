/**
 * @brief Defines a FIFO queue structure
 */

#pragma once

#include <vector>

#include "list.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Queue
 * @brief A generic FIFO (First-In-First-Out) queue implementation.
 *
 * The Queue class provides standard queue operations like enqueue and dequeue,
 * implementing the FIFO principle where elements are removed in the same order
 * they were added.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class Queue : protected List<T> {
public:

	/**
	 * @brief Default constructor that initializes an empty queue.
	 */
	Queue() : List<T>() {}

	/**
	 * @brief Constructor that initializes a queue with a custom comparator.
	 * @param comparator The comparator function to use for element comparison
	 */
	Queue(Comparator<T> comparator) : List<T>(comparator) {}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the queue.
	 * @param il (`std::initializer_list`) a list of values to seed the queue
	 */
	Queue(std::initializer_list<T> il) : List<T>(il) {}

	/**
	 * @brief Destructor that cleans up queue resources.
	 */
	~Queue() {
		List<T>::clear();
	}

	/**
	 * @brief Checks if the contents of two given queue objects are equal
	 * @param q (`Queue &`) the queue to compare against
	 * @return true if both queues have the same values, otherwise false
	 */
	bool operator==(const Queue<T> &q) const {
		return List<T>::operator==(q);
	}

	/**
	 * @brief Checks if the contents of two given queue objects are not equal
	 * @param q (`Queue &`) the queue to compare against
	 * @return false if both queues have the same values, otherwise true
	 */
	bool operator!=(const Queue<T> &q) const {
		return List<T>::operator!=(q);
	}

 	/**
	 * @brief adds a single item to the queue (enqueue)
	 * @param data (`T`) the data element to add to the queue
	 * @return a reference to the Queue
	 */
	Queue<T> &operator+=(const T data) {
		this->enqueue(data);
		return *this;
	}

	/**
	 * @brief Creates a copy of the Queue as a vector
	 * @returns a `vector<T>` of the Queue contents
	 */
	std::vector<T> array() {
		return List<T>::array();
	}

	/**
	 * @brief returns the item at the end of the queue
	 * @returns a `T` object at the back of the queue
	 */
	T back() {
		return **this->getBack();
	}

	/**
	 * @brief Removes and returns the element at the front of the queue.
	 * @return The element at the front of the queue
	 * @throws std::out_of_range if the queue is empty
	 */
	T dequeue() {
		return this->removeAt(0);
	}

	/**
	 * @brief Removes all elements from the queue and returns them as a vector.
	 * @return A vector containing all elements in the queue in order
	 */
	std::vector<T> drain() {
		std::vector<T> all = this->array();
		this->clear();
		return all;
	}

	/**
	 * @brief Removes the first occurrence of the specified element from the queue.
	 * @param data The element to remove
	 * @return The removed element
	 * @throws std::range_error if the element is not found in the queue
	 */
	T eject(T data) {
		return this->removeValue(data);
	}

	/**
	 * @brief Adds an element to the back of the queue.
	 * @param data The element to add
	 */
	void enqueue(T data) {
		this->insert(data, Position::BACK);
	}

	/**
	 * @brief returns the item at the front of the queue
	 * @returns a `T` object at the front of the queue
	 */
	T front() {
		return **this->getFront();
	}

	/**
	 * @brief the number of elements in the queue
	 * @returns a `size_t` of the number of elements in the queue
	 */
	size_t size() const {
		return this->_size;
	}
};

}  // namespace ds
