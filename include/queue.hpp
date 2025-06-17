/**
 * @brief Defines a FIFO queue structure
 */

#pragma once

#include "list.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

template<typename T>
class Queue : public List<T> {

public:
	/**
	 * @brief Default constructor that initializes an empty queue.
	 */
	Queue() : List<T>() {}

	/**
	 * @brief Constructor that initializes a queue with a custom comparator.
	 *
	 * @param comparator The comparator function to use for element comparison
	 */
	Queue(Comparator<T> comparator) : List<T>(comparator) {}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the collection.
	 *
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	Queue(std::initializer_list<T> il) {
		for (auto it: il) {
			this->insert(it);
		}
	}

	/**
	 * @brief Destructor that cleans up queue resources.
	 */
	~Queue() {
		this->clear();
	}

    void enqueue(T data) {
        this->insert(data, Position::BACK);
    }

    void push(T data) {
        this->insert(data, Position::BACK);
    }


};

}
