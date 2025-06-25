/**
 * @brief Defines the Stack data structure, a LIFO (Last In, First Out) collection.
 */

#pragma once

#include <algorithm>
#include <exception>
#include <memory>
#include <vector>

#include "list.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class Stack
 * @brief A generic stack class template for tree-like data structures.
 *
 * This class represents a stack data structure.  A stack is a fundamental abstract
 * data type (ADT) that serves as a collection of elements, operating on a **Last In,
 * First Out (LIFO)** principle.
 *
 * @tparam T The type of data stored within the stack.
 */
template<typename T>
class Stack : protected List<T> {
public:

	Stack() : List<T>() {}

	/**
	 * @brief a copy constructor for Stack object
	 * @param stack (`Stack<T> &`) the stack that will be copied
	 */
	Stack(Stack<T> &stack) : List<T>() {
		std::vector<T> v = stack.array();
		std::reverse(v.begin(), v.end());

		for (auto it: v) {
			this->push(it);
		}
	}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the collection.
	 *
	 * The stack initializer will take the items from left to right and push
	 * them into the stack.
	 *
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	Stack(std::initializer_list<T> il) : List<T>() {
		for (auto it: il) {
			this->push(it);
		}
	}

	~Stack() {
		clear();
	}

	/**
	 * @brief Overloads the stream insertion operator for Stack objects.
	 *
	 * Allows printing a Stack object directly to an output stream, using its
	 * `str()` method for representation.
	 * @param st (`std::ostream`) the output stream
	 * @param stack (`Stack<T> &`) the Stack object to print
	 * @returns a reference to the `std::ostream` object
	 */
	friend std::ostream &operator<<(std::ostream &st, const Stack<T> &stack) {
		return st << stack.str();
	}

	/**
	 * @brief adds a single item to the stack
	 * @param data (`T`) the data element to add to the stack
	 * @return a reference to the stack
	 */
	Stack<T> &operator+=(const T data) {
		this->push(data);
		return *this;
	}

	/**
	 * @brief Checks if the contents of two given stack objects are equal
	 * @param stack (`Stack &`) the stack to compare against
	 * @return true if both stacks have the same values, otherwise false
	 */
	bool operator==(const Stack<T> &stack) const {
		return List<T>::operator==(stack);
	}

	/**
	 * @brief Checks if the contents of two given stack objects are not equal
	 * @param stack (`Stack &`) the stack to compare against
	 * @return false if both lists have the same values, otherwise true
	 */
	bool operator!=(const Stack<T> &stack) const {
		return List<T>::operator!=(stack);
	}

	/**
	 * @brief Operator to clear the stack.
	 *
	 * This is a convenience wrapper for the `clear` function, resetting the
	 * stack's size to zero.
	 *
	 * @return A reference to the current object (`*this`).
	 */
	Stack<T> &operator~() {
		clear();
		return *this;
	}

	/**
	 * @brief copies the current stack into an array vector and returns it.
	 *
	 * This array copy operation does not change the current stack.  This is a
	 * new vector that is a snapshot of the stack in time.  It does not
	 * track any changes once the current statck deviates.  Each call will return
	 * a new vector.
	 *
	 * @returns a `vector<T>` collection that contains each element of the stack
	 */
	std::vector<T> array(void) {
		return List<T>::array();
	}

	/**
	 * Empties the stack and resets it.  It will remove all entries from the
	 * stack and free up associated memory.
	 */
	void clear() {
		List<T>::clear();
	}

	/**
	 * @brief Checks if a `T` data element exists within the stack
	 * @returns true if the data element exists in the stack, otherwise false.
	 */
	bool contains(T data) {
		return List<T>::contains(data);
	}

	/**
	 * @brief returns the contents of the stack as a JSON string
	 * @returns a string that holds the stack in a JSON string
	 */
	std::string json() const override {
		return List<T>::json();
	}

	/**
	 * @brief A convenience wrapper for the top function.
	 * @returns A copy of the data element `T` at the top of the stack
	 */
	T peek() {
		return top();
	}

	/**
	 * Retrieves the top item from the stack and returns it.  An item is
	 * is removed from the stack.
	 *
	 * @returns the data at the stop of the stack
	 */
	T pop() {
		return List<T>::removeAt(0);
	}

	/**
	 * Puts a data element on the top of the stack.
	 * @param data (`T`) the data element to store in the stack
	 */
	void push(T data) {
		List<T>::insert(data, Position::FRONT);
	}

	/**
	 * The current size of the stack
	 * @returns a size_t value that represents the size of the stack
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

	/**
	 * @returns: The data element on the top of the stack.  This does not remove
	 * the item from the top.
	 */
	T top() {
		if (this->_size == 0) {
			throw std::out_of_range("Cannot get the top of an empty stack");
		}

		return List<T>::front();
	}
};
}  // namespace ds
