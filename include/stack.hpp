#pragma once

#include <exception>
#include <memory>

#include "collection.hpp"

namespace ds {
template<typename T>
class Stack : public Collection<T> {
public:

	Stack() : Collection<T>() {}

	~Stack() {
		clear();
	}

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

		this->length = 0;
		this->first = nullptr;
		this->last = nullptr;
		this->root = nullptr;
	}

	/**
	 * A convenience wrapper for the top function.
	 *
	 * Returns:
	 *     A copy of the data element at the top of the stack
	 */
	T peek() {
		return top();
	}

	/**
	 * Retrieves the top item from the stack and returns it.  An item is
	 * is removed from the stack.
	 *
	 * Returns:
	 *    The data at the stop of the stack
	 */
	T pop() {
		T data;

		if (this->root != nullptr) {
			data = this->root->getData();
			std::shared_ptr<Node<T>> topNode = this->root;
			this->root = this->root->getRight();
			this->first = this->root;
			topNode = nullptr;
			this->length--;
			return data;
		}

		throw std::runtime_error("Trying to remove from empty stack");
	}

	/**
	 * Puts a data element on the top of the stack.
	 *
	 * Arguments:
	 *     - data (`T`) -- the data element to store in the stack
	 *
	 * Returns:
	 *     Nothing
	 */
	void push(T data) {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->root == nullptr) {
			this->root = node;
			this->last = this->root;
		} else {
			node->setRight(this->root);
			this->root->setParentId(node->getId());
			this->root = node;
		}

		this->first = node;
		this->length++;
	}

	std::string str() const override {
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
	 * Returns:
	 *    The data element on the top of the stack.  This does not remove the item from
	 *    the top.
	 */
	T top() {
		if (this->length == 0) {
			throw std::runtime_error("Cannot get the top of an empty stack");
		}

		return this->root->getData();
	}
};
}  // namespace ds
