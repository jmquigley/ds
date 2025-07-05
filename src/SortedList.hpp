#pragma once

#include <Comparator.hpp>
#include <List.hpp>
#include <iostream>
#include <typeinfo>

namespace ds {

/**
 * @class SortedList
 * @brief A special list implementation that sorts entries as they are inserted.
 *
 * This list structure inherits from the general list and overrides the insert
 * method to add an item into its sorted location.  It uses a `Comparator` to
 * find the proper location as compared to other elements in the collection.
 *
 * @tparam T The type of data stored within the queue.
 */
template<typename T>
class SortedList : public List<T> {
public:

	SortedList() : List<T>() {}

	/**
	 * @brief Constructor that sets a custom `Comparator` object
	 * @param comparator (`Comparator`) a reference to a comparison object
	 */
	SortedList(Comparator<T> comparator) : List<T>(comparator) {}

	/**
	 * @brief Copy constructor
	 * @param slist (`SortedList<T>`) the sorted list to copy
	 */
	SortedList(SortedList<T> &slist) : List<T>(slist) {}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the collection.
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	SortedList(std::initializer_list<T> il) : List<T>() {
		for (auto it: il) {
			this->insert(it);
		}
	}

	/**
	 * @brief Inserts an element into a list based on its comparator position.
	 * @param data The element to insert
	 */
	virtual void insert(T data) override {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->_root == nullptr) {
			// empty list, first value
			this->_root = node;
			this->_front = this->_back = node;
		} else {
			std::shared_ptr<Node<T>> tnode = this->_root;

			while (tnode && (this->comparator(data, tnode->getData()) > 0)) {
				tnode = tnode->getRight();
			}

			if (tnode == this->_root) {
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

		this->_size++;
	}
};

}  // namespace ds
