#pragma once

#include <ds/List.hpp>
#include <ds/Replicate.hpp>
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
	 * @brief a Queue move constructor
	 * @param q (`Queue<T> &&`) an rvalue queue reference to copy
	 */
	constexpr Queue(Queue<T> &&q) noexcept : Queue() {
		this->move(std::move(q));
	}

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
	Queue<T> &operator=(const Queue<T> &q) {
		List<T>::operator=(q);
		return *this;
	}

	/**
	 * @brief Move assignment operator for Queue
	 *
	 * Transfers ownership of resources from another Queue to this Queue
	 *
	 * @param q The Queue to move resources from
	 * @returns Reference to this Queue after assignment
	 */
	Queue<T> &operator=(Queue<T> &&q) noexcept {
		this->move(std::move(q));
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
	Queue<T> &operator+=(const T data) override {
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
	void clear() override {
		List<T>::clear();
	}

	/**
	 * @brief Checks if an element exists in the Queue
	 * @returns true if the item is in the Queue otherwise false
	 */
	bool contains(T data) override {
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
	 * @brief Executes a callback function for each element in the queue
	 *
	 * Iterates through all elements in the queue sequentially, calling the
	 * provided callback function for each element with its index and a
	 * reference to its data value.
	 *
	 * @tparam Callback A callable type that accepts (size_t, T&) parameters
	 * @param callback The function to execute for each element.
	 *                 First argument is the element's index (0-based)
	 *                 Second argument is a reference to the element's data
	 *
	 * @note The callback receives the data by reference, so modifications
	 *       to the data will affect the list contents.
	 */
	template<typename Callback>
	void each(Callback callback) {
		List<T>::each(callback);
	}

	/**
	 * @brief Check if the queue is empty
	 * @return true if the queue is empty, otherwise false
	 */
	bool empty() const override {
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
	std::string json() const override {
		return List<T>::json();
	}

	/**
	 * @brief returns the item at the front of the queue
	 * @returns a `T` object at the front of the queue
	 */
	T maximum() const override {
		return List<T>::maximum();
	}

	/**
	 * @brief returns the item at the end of the queue
	 * @returns a `T` object at the back of the queue
	 */
	T minimum() const override {
		return List<T>::minimum();
	}

	/**
	 * @brief the number of elements in the queue
	 * @returns a `size_t` of the number of elements in the queue
	 */
	size_t size() const {
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
