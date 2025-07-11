#pragma once

#include <BinaryTree.hpp>
#include <Comparator.hpp>
#include <format>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace ds {

/**
 * @class Priority
 * @brief Represents an element in the priority queue with a priority value and
 * data
 *
 * @tparam T The type of data being stored in the priority queue
 */
template<typename T>
class Priority {
	/// @brief The actual priority value associated with this element in the
	/// queue
	PROPERTY(value, Value, std::string);
	/// @brief The data associated with this priority value
	PROPERTY(data, Data, T);
};

/**
 * @class PriorityComparator
 * @brief Defines how priority elements are compared for ordering in the queue
 *
 * This comparator determines the relative ordering of elements based on their
 * priority values. Higher values indicate higher priority.
 *
 * @tparam T The type of data being stored in the priority queue
 */
template<typename T>
class PriorityComparator : public Comparator<T> {
public:

	/**
	 * @brief Compares two Priority objects based on their value property
	 *
	 * @param o1 First Priority object
	 * @param o2 Second Priority object
	 * @return int Positive if o1 > o2, negative if o1 < o2, zero if equal
	 */
	int compare(const Priority<T> o1, const Priority<T> o2) const override {
		if (o1.value() == o2.value()) {
			return 0;
		} else if (o1.value() > o2.value()) {
			return 1;
		}

		return -1;
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
	PriorityQueue() : BinaryTree<Priority<T>>(PriorityComparator<T>()) {}

	/**
	 * @brief Allows for the use of an initializer list to seed the Priority
	 * queue.
	 * @param il (`std::initializer_list`) a list of values to seed the
	 * queue.
	 */
	PriorityQueue(std::initializer_list<T> il)
		: PriorityQueue<Priority<T>>(), BinaryTree<Priority<T>>(il) {}

	/**
	 * @brief Destroys the priority queue and frees all resources
	 */
	~PriorityQueue() {
		this->clear();
	}

	/**
	 * @brief Converts the priority queue to an array
	 *
	 * @return std::vector<T> Vector containing all elements in priority order
	 */
	std::vector<T> array() {
		// TODO: add array() to the PriorityQueue
		std::vector<T> out;
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
	T dequeue() {
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
	std::vector<T> drain() {
		// TODO: add drain() to the PriorityQueue
	}

	/**
	 * @brief Adds a new element with specified priority to the queue
	 *
	 * @param data The element to be added
	 * @param priority The priority level as a numerical value
	 */
	void enqueue(T data, size_t priority) {
		// TODO: adds enqueue() to the PriorityQueue
	}
};

}  // namespace ds
