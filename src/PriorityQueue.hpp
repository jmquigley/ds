#pragma once

#include <BinaryTree.hpp>
#include <Comparator.hpp>
#include <format>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace ds {

/**
 * @class Priority
 * @brief Represents an element in the priority queue with a priority value,
 * data, and an offset
 *
 * The Priority class encapsulates the data and its associated priority in the
 * queue. Higher priority values indicate higher priority in the queue. The
 * offset is used to disambiguate entries with the same priority value.
 *
 * @tparam T The type of data being stored in the priority queue
 */
template<typename T>
class Priority {
	/// @brief The data associated with this priority value
	PROPERTY(data, Data, T);

	/// @brief The actual priority value associated with this element in the
	/// queue Higher values indicate higher priority
	PROPERTY(value, Value, size_t);

	/// @brief Offset key appended to the priority value to ensure uniqueness
	/// when multiple items have the same priority
	PROPERTY(offset, Offset, size_t);

public:

	Priority() : _data({}), _value(0), _offset(0) {}

	/**
	 * @brief Constructs a Priority object
	 *
	 * @param data The data to be stored
	 * @param value The priority value (higher value = higher priority)
	 * @param offset A unique identifier for entries with the same priority
	 */
	Priority(T data, size_t value, size_t offset)
		: _data(data), _value(value), _offset(offset) {}

	/**
	 * @brief copy constructor for PriorityQueue
	 * @param priority the `Priority<T>` object to copy
	 */
	Priority(const Priority &priority) : Priority<T>() {
		this->operator=(priority);
	}

	virtual ~Priority() {}

	/**
	 * @brief equal operator to assign a Priority to another.
	 *
	 * Works like the copy constructor to copy all elements of one Priority
	 * to another.
	 * @param priority the `Priority<T>` object to copy
	 * @returns a reference to the object that is being copied into
	 */
	Priority<T> &operator=(const Priority<T> &priority) {
		if (this != &priority) {
			this->_data = priority._data;
			this->_value = priority._value;
			this->_offset = priority._offset;
		}
		return *this;
	}

	/**
	 * @brief Equality comparison operator
	 *
	 * @param other The Priority object to compare with
	 * @return true if both priorities have the same value
	 * @return false otherwise
	 */
	bool operator==(const Priority &other) const {
		return this->key() == other.key();
	}

	/**
	 * @brief Greater-than comparison operator
	 *
	 * @param other The Priority object to compare with
	 * @return true if this priority is greater than the other
	 * @return false otherwise
	 */
	bool operator>(const Priority &other) const {
		return this->key() > other.key();
	}

	/**
	 * @brief Less-than comparison operator
	 *
	 * @param other The Priority object to compare with
	 * @return true if this priority is less than the other
	 * @return false otherwise
	 */
	bool operator<(const Priority &other) const {
		return this->key() < other.key();
	}

	/**
	 * @brief Stream insertion operator for Priority objects
	 *
	 * Allows Priority objects to be directly written to output streams.
	 * This enables convenient printing of Priority objects using standard
	 * output operators.
	 *
	 * Example usage:
	 * ```cpp
	 * Priority<int> p(42, 10, 1);
	 * std::cout << p; // Outputs the string representation of the Priority
	 * object
	 * ```
	 *
	 * @tparam T The type of data stored in the Priority object
	 * @param st The output stream to write to
	 * @param pri The Priority object to output
	 * @return std::ostream& Reference to the output stream for chaining
	 *
	 * @see str() Returns the string representation used by this operator
	 */
	friend std::ostream &operator<<(std::ostream &st, const Priority<T> &pri) {
		return st << pri.str();
	}

	/**
	 * @brief Generates a unique string key for this priority
	 *
	 * The key combines the priority value and offset to ensure uniqueness
	 * even when priority values are identical.
	 *
	 * @return std::string A formatted string key in the format "value:offset"
	 */
	std::string key() const {
		return std::format("{:09d}:{:09d}", _value, _offset);
	}

	/**
	 * @brief creates a string representation of the Priority object.
	 * @returns a string representation of the Priority object.
	 */
	std::string str() const {
		std::stringstream ss;
		ss << std::quoted("data") << ":" << std::quoted(_data) << ", "
		   << std::quoted("key") << ":" << std::quoted(this->key());
		return ss.str();
	}
};

/**
 * @class PriorityQueue
 * @brief A queue data structure that processes elements according to priority
 *
 * This priority queue implementation uses a binary tree as its underlying
 * data structure to efficiently manage priorities. Elements with higher
 * priority values are processed before elements with lower priority.
 *
 * @tparam T The type of data being stored in the priority queue
 */
template<typename T>
class PriorityQueue : protected BinaryTree<Priority<T>> {
private:

	/**
	 * @brief Map used to make same priority values unique
	 *
	 * These values are used to ensure consistent ordering of elements
	 * with equal priorities by tracking offset counts for each priority.
	 */
	std::map<size_t, size_t> offsets;

public:

	/**
	 * @brief Constructs an empty priority queue
	 */
	PriorityQueue() : BinaryTree<Priority<T>>() {}

	/**
	 * @brief a copy construcgtor for the PriorityQueue
	 * @param pq (`PriorityQueue<T>`) reference to the priority queue to
	 * copy.
	 */
	PriorityQueue(PriorityQueue<T> &pq) : PriorityQueue<T>() {
		this->operator=(pq);
	}

	/**
	 * @brief Allows for the use of an initializer list to seed the Priority
	 * queue.
	 * @param il (`std::initializer_list`) a list of values to seed the
	 * queue.
	 */
	PriorityQueue(std::initializer_list<Priority<T>> il)
		: BinaryTree<Priority<T>>(il) {}

	/**
	 * @brief Destroys the priority queue and frees all resources
	 */
	virtual ~PriorityQueue() {
		this->clear();
	}

	/**
	 * @brief the equal operator for the PriorityQueue class
	 * @param pq (`PriorityQueue<T>`) reference to the priority queue to
	 * copy.
	 * @returns a reference to the this pointer for the class
	 */
	PriorityQueue<T> &operator=(PriorityQueue<T> &pq) {
		this->offsets = pq.offsets;
		BinaryTree<Priority<T>>::operator=(pq);
		return *this;
	}

	/**
	 * @brief Converts the priority queue to an array
	 *
	 * Creates a `std::vector<T>` from the current priority queue, but does
	 * not remove all of the elements.  To remove the elements use .drain().
	 *
	 * @return std::vector<T> Vector containing all elements in priority order
	 */
	std::vector<Priority<T>> array() {
		std::vector<Priority<T>> out;
		this->inorder([&](auto &node) { out.push_back(node.getData()); });
		return out;
	}

	/**
	 * @brief Removes all elements from the priority queue
	 *
	 * Deletes everything from the current priority queue and resets it
	 * to its initialized state.
	 */
	void clear() {
		BinaryTree<Priority<T>>::clear();
		offsets.clear();
	}

	/**
	 * @brief Retrieves and removes the highest priority element
	 *
	 * @return T The data element with the highest priority
	 * @throws std::range_error if the queue is empty
	 */
	Priority<T> dequeue() {
		if (this->size() == 0) {
			throw std::range_error("Priority queue is empty");
		}

		return BinaryTree<Priority<T>>::removeFirst();
	}

	/**
	 * @brief Removes all elements and returns them as an array
	 *
	 * @return std::vector<T> Vector containing all elements in priority order
	 */
	std::vector<Priority<T>> drain() {
		std::vector<Priority<T>> out;

		while (this->size() > 0) {
			out.push_back(dequeue());
		}

		return out;
	}

	/**
	 * @brief Checks if the priority queue is empty
	 *
	 * Determines whether the priority queue contains no elements.
	 * This method provides a convenient way to check if the queue is empty
	 * without needing to check if the size is zero.
	 *
	 * @return true if the priority queue contains no elements
	 * @return false if the priority queue contains at least one element
	 */
	bool empty() const {
		return BinaryTree<Priority<T>>::empty();
	}

	/**
	 * @brief Adds an element to the priority queue with the specified priority
	 *
	 * This method inserts a new element into the priority queue with the given
	 * priority value. Elements with higher priority values are dequeued before
	 * elements with lower priority. If multiple elements have the same
	 * priority, they are dequeued in the order they were enqueued (FIFO
	 * behavior within the same priority level).
	 *
	 * The method automatically assigns a unique offset to each element to
	 * maintain insertion order for elements with identical priorities.
	 *
	 * @param data The element to be added to the priority queue
	 * @param priorityValue The priority value to assign to the element (higher
	 * values = higher priority)
	 * @return Priority<T> The Priority object that was created and inserted
	 *
	 * @note Time complexity: O(log n) where n is the number of elements in the
	 * queue
	 *
	 * @see dequeue() Removes and returns the highest priority element
	 * @see enqueue(Priority<T>) Overload that accepts a pre-constructed
	 * Priority object
	 *
	 * Example:
	 * ```cpp
	 * PriorityQueue<std::string> queue;
	 * queue.enqueue("Critical task", 100); // Highest priority
	 * queue.enqueue("Normal task", 50);    // Medium priority
	 * queue.enqueue("Low priority task", 10); // Lowest priority
	 * ```
	 */
	Priority<T> enqueue(T data, size_t priorityValue) {
		if (!offsets.contains(priorityValue)) {
			offsets[priorityValue] = 0;
		}

		size_t offset = ++offsets[priorityValue];
		offsets[priorityValue] = offset;

		Priority<T> priority {data, priorityValue, offset};

		this->insert(priority);
		return priority;
	}

	/**
	 * @brief Adds a pre-constructed Priority object to the priority queue
	 *
	 * This overload accepts an already constructed Priority object and inserts
	 * it into the priority queue. It updates the internal offset tracking to
	 * ensure future elements with the same priority maintain proper FIFO
	 * ordering.
	 *
	 * This method is primarily used internally by the public enqueue method,
	 * but can also be used directly when you need complete control over
	 * Priority object creation.
	 *
	 * @param priority The Priority object to be inserted
	 * @return Priority<T> The same Priority object that was inserted (for
	 * chaining)
	 *
	 * @note Time complexity: O(log n) where n is the number of elements in the
	 * queue
	 *
	 * @see enqueue(T, size_t) Convenience overload that constructs the Priority
	 * object
	 */
	Priority<T> enqueue(Priority<T> priority) {
		offsets[priority.value()] = priority.offset();
		this->insert(priority);
		return priority;
	}

	/**
	 * @brief Retrieves the smallest value in the tree
	 * @returns the smallest value in the priority queue
	 */
	Priority<T> minimum() const {
		return BinaryTree<Priority<T>>::minimum();
	}

	/**
	 * @brief Retrieves the size of the Priority queue
	 * @returns the size of the priority queue
	 */
	size_t size() const {
		return BinaryTree<Priority<T>>::size();
	}
};

}  // namespace ds
