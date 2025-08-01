#pragma once

#include <ds/List.hpp>
#include <vector>

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
	 * @brief the copy constructor for the Queue class
	 * @param q (`Queue<T>`) the queue object to copy
	 */
	Queue(Queue<T> &q) : Queue() {
		this->operator=(q);
	}

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
		this->clear();
	}

	/**
	 * @brief equality operator for the Queue class
	 * @param q (`Queue<T> &`) a reference to teh queue to copy
	 * @returns a reference to the this pointer for the object
	 */
	Queue<T> &operator=(Queue<T> &q) {
		List<T>::operator=(q);
		return *this;
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
	virtual Queue<T> &operator+=(const T data) override {
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
	 * @brief deletes everything from the current queue and resets it to its
	 * initialized state.
	 */
	void clear() {
		List<T>::clear();
	}

	/**
	 * @brief Checks if an element exists in the Queue
	 * @returns true if the item is in the Queue otherwise false
	 */
	inline bool contains(T data) {
		return List<T>::contains(data);
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
	 * @brief Check if the queue is empty
	 * @return true if the queue is empty, otherwise false
	 */
	bool empty() {
		return List<T>::empty();
	}

	/**
	 * @brief Removes the first occurrence of the specified element from the
	 * queue.
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
	 * @brief returns the contents of the stack as a JSON string
	 * @returns a string that holds the stack in a JSON string
	 */
	std::string json() const {
		return List<T>::json();
	}

	/**
	 * @brief returns the item at the front of the queue
	 * @returns a `T` object at the front of the queue
	 */
	inline T maximum() const {
		return List<T>::maximum();
	}

	/**
	 * @brief returns the item at the end of the queue
	 * @returns a `T` object at the back of the queue
	 */
	inline T minimum() const {
		return List<T>::minimum();
	}

	/**
	 * @brief the number of elements in the queue
	 * @returns a `size_t` of the number of elements in the queue
	 */
	inline size_t size() const {
		return List<T>::size();
	}

	/**
	 * @brief Returns a string representation of the stack.
	 *
	 * Currently, it formats the stack's data into a simple JSON-like string.
	 * @return A string representing the node's content.
	 */
	std::string str() const override {
		return List<T>::str();
	}
};

}  // namespace ds
