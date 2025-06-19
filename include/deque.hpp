/**
 * @brief Defines a deque double ended queue structure
 *
 * A deque (double-ended queue) is a data structure that allows insertion and
 * removal of elements from both ends efficiently. It combines the features of
 * stacks and queues
 */

#pragma once

#include <vector>

#include "queue.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Deque
 * @brief A double ended queue
 *
 * The Deque provides a queue that allows for changes at both ends.  It can be
 * used as a method for aging itens in the queue.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class Deque : public Queue<T> {
public:

	/**
	 * @brief Default constructor that initializes an empty deque.
	 */
	Deque() : Queue<T>() {}

	/**
	 * @brief Constructor that initializes a deque with a custom comparator.
	 * @param comparator The comparator function to use for element comparison
	 */
	Deque(Comparator<T> comparator) : Queue<T>(comparator) {}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the queue.
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	Deque(std::initializer_list<T> il) {
		for (auto it: il) {
			this->insert(it);
		}
	}

	/**
	 * @brief Destructor that cleans up deque resources.
	 */
	~Deque() {
		this->clear();
	}
};

}  // namespace ds
