#pragma once

#include "collection.hpp"

namespace ds {
template<typename T>
class Stack : public Collection<T> {
public:

	Stack() : Collection<T>() {}

	~Stack() {}

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
	 * Puts a data element on the top of the stack.
	 *
	 * Arguments:
	 *     - data (`T`) -- the data element to store in the stack
	 *
	 * Returns:
	 *     Nothing
	 */
	void push(T data) {
		Node<T> node = new Node<T>(data);

		if (this->root == nullptr) {
			this->root = node;
			this->last = this->root;
		} else {
			node.setRight(this->root);
			this->root.setParentId(node.getId());
			this->root = node;
		}

		this->first = node;
		this->length++;
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
			data = this->root.getData();
			Node<T> *topNode = this->root;
			this->root = this->root.getRight();
			this->first = this->root;
			if (topNode != nullptr) {
				delete topNode;
			}
		}

		return data;
	}

    T top() {
        return this->root.getData();
    }


};
}  // namespace ds
