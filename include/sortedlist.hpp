#pragma once

#include <iostream>
#include <typeinfo>

#include "comparator.hpp"
#include "list.hpp"

namespace ds {

template<typename T>
class SortedList : public List<T> {
public:

	SortedList() : List<T>() {}

	SortedList(Comparator<T> comparator) : List<T>(comparator) {}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the collection.
	 *
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	SortedList(std::initializer_list<T> il) {
		for (auto it: il) {
			this->insert(it);
		}
	}

	virtual void insert(T data) override {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

        if (this->root == nullptr) {
            // empty list, first value
            this->root = this->front = this->back = node;
        } else {
            std::shared_ptr<Node<T>> tnode = this->root;

            while (tnode && (this->comparator(data, tnode->getData()) > 0)) {
                tnode = tnode->getRight();
            }

            if (tnode == this->root) {
                this->addFront(node);
            } else if (tnode == nullptr) {
                this->addBack(node);
            } else {
                node->setRight(tnode);
                node->setLeft(tnode->getLeft());
                tnode->getLeft()->setRight(node);
                tnode->setLeft(node);
            }
        }

        this->size++;
    }
};

}  // namespace ds
