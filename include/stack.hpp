/**
 * @file stack.hpp
 * @brief Defines the Stack data structure, a LIFO (Last In, First Out) collection.
 */

#pragma once

#include <exception>
#include <memory>

#include "collection.hpp"

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
class Stack : public Collection<T> {
public:

	Stack() : Collection<T>() {}

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
	 * Empties the stack and resets it.  It will remove all entries from the
	 * stack and free up associated memory.
	 */
	void clear() override {
		if (this->root != nullptr) {
			std::shared_ptr<Node<T>> node = this->root;
			std::shared_ptr<Node<T>> next;

			while (node) {
				next = node->getRight();
				node = nullptr;
				node = next;
			}
		}

		this->size = 0;
		this->front.reset();
		this->back.reset();
		this->root.reset();
	}

    /**
     * @brief returns the contents of the stack as a JSON string
     * @returns a string that holds the stack in a JSON string
     */
	std::string json() const override {
		std::stringstream ss;

		if (this->root != nullptr) {
			std::shared_ptr<Node<T>> node = this->root;
			std::shared_ptr<Node<T>> next;

			ss << "[";
			std::string comma = "";
			while (node) {
				next = node->getRight();
				ss << comma << *node;
				node = next;
				comma = ",";
			}
			ss << "]";
		}

		return ss.str();
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
		T data;

		if (this->root != nullptr) {
			data = this->root->getData();
			std::shared_ptr<Node<T>> topNode = this->root;
			this->root = this->root->getRight();
			this->front = this->root;
			topNode = nullptr;
			this->size--;
			return data;
		}

		throw std::runtime_error("Trying to remove from empty stack");
	}

	/**
	 * Puts a data element on the top of the stack.
	 * @param data (`T`) the data element to store in the stack
	 */
	void push(T data) {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->root == nullptr) {
			this->root = node;
			this->back = this->root;
		} else {
			node->setRight(this->root);
			this->root->setParentId(node->getId());
			this->root = node;
		}

		this->front = node;
		this->size++;
	}

	/**
	 * @brief Returns a string representation of the stack.
	 *
	 * Currently, it formats the stack's data into a simple JSON-like string.
	 * @return A string representing the node's content.
	 */
	std::string str() const override {
        return json();
	}

	/**
	 * @returns: The data element on the top of the stack.  This does not remove
	 * the item from the top.
	 */
	T top() {
		if (this->size == 0) {
			throw std::runtime_error("Cannot get the top of an empty stack");
		}

		return this->root->getData();
	}
};
}  // namespace ds
