#pragma once

#include <ds/List.hpp>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

namespace ds {

/**
 * @class SortedList
 * @brief A specialized list implementation that automatically maintains
 * elements in sorted order
 *
 * This container inherits from the general List class and overrides the insert
 * method to add elements in their proper sorted position.
 *
 * Unlike standard sorting algorithms that rearrange elements after insertion,
 * SortedList ensures elements are always in the correct position as they are
 * added, providing efficient lookups and ordered traversal at all times.
 *
 * @tparam T The type of data stored within the sorted list
 */
template<typename T>
class SortedList : public List<T> {
private:

	/**
	 * @brief Deleted to prevent unordered operations
	 * @note These operations would violate the sorted property of the list
	 */
	std::vector<T> reverse() = delete;

	/**
	 * @brief Deleted to prevent unordered operations
	 * @note These operations would violate the sorted property of the list
	 */
	void shuffle() = delete;

	/**
	 * @brief Deleted to prevent unordered operations
	 * @note These operations would violate the sorted property of the list
	 */
	void swap(size_t pos1, size_t pos2) = delete;

public:

	/**
	 * @brief Default constructor
	 *
	 * Creates an empty sorted list using the default comparator for type T
	 */
	SortedList() : List<T>() {}

	/**
	 * @brief Copy constructor
	 *
	 * Creates a new sorted list as a deep copy of an existing one,
	 * preserving the sorted order of elements.
	 *
	 * @param slist A reference to the sorted list to copy
	 */
	SortedList(const SortedList<T> &slist) : List<T>(slist) {}

	/**
	 * @brief Move constructor
	 *
	 * Efficiently transfers ownership of resources from an existing sorted list
	 * to a new one without copying elements.
	 *
	 * @param slist An rvalue reference to a sorted list whose resources will be
	 * moved
	 */
	SortedList(SortedList<T> &&slist) : List<T>(std::move(slist)) {}

	/**
	 * @brief Initializer list constructor
	 *
	 * Creates a sorted list from the provided initializer list,
	 * automatically inserting elements in their sorted positions.
	 *
	 * @param il An initializer list containing values to populate the list with
	 */
	SortedList(const std::initializer_list<T> &il) : List<T>() {
		for (const auto &it: il) {
			this->insert(it);
		}
	}

	/**
	 * @brief Copy assignment operator
	 *
	 * Assigns the contents of another sorted list to this one,
	 * replacing any existing elements.
	 *
	 * @param other The sorted list to copy from
	 * @return Reference to this sorted list after assignment
	 */
	SortedList<T> &operator=(const SortedList<T> &other) {
		List<T>::operator=(other);
		return *this;
	}

	/**
	 * @brief Initializer list assignment operator
	 *
	 * Replaces the contents of the sorted list with elements from the
	 * initializer list, inserting them in sorted order.
	 *
	 * @param il An initializer list containing values to populate the list with
	 * @return Reference to this sorted list after assignment
	 */
	SortedList<T> &operator=(const std::initializer_list<T> &il) {
		List<T>::operator=(il);
		return *this;
	}

	/**
	 * @brief Inserts an element into its sorted position in the list
	 *
	 * This method overrides the base class insert to place the element
	 * in its correct position according to the list's ordering. It uses
	 * the comparator to determine where the element should be inserted.
	 *
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

			while (tnode && (data > tnode->getData())) {
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
