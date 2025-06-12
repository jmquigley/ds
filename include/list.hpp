/**
 * @file list.hpp
 * @brief Defines a doubly linked list data structure collection.
 */

#pragma once

#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "collection.hpp"
#include "helpers.hpp"
#include "iterable.hpp"
#include "iterator.hpp"
#include "property.hpp"

/**
 * @namespace ds
 * @brief Contains data structure related classes.
 */
namespace ds {

/**
 * @class List
 * @brief A generic doubly linked list class.
 * @tparam T The type of data stored within the list.
 */
template<typename T>
class List : public Collection<T>, public Iterable<T> {
private:

	/**
	 * @brief Retrieves the node at the specified index.
	 * @param index (`size_t`) The index of the node to retrieve, or a Position enum value
	 * @return std::shared_ptr<Node<T>> Pointer to the node at the specified index
	 * @throws std::out_of_range If the index is out of valid range
	 */
	std::shared_ptr<Node<T>> getNodeByIndex(size_t index) {
		// Convert Position enum values to actual indices
		if (index == as_integer(Position::BACK)) {
			index = this->getSize() - 1;
		} else if (index == as_integer(Position::FRONT)) {
			index = 0;
		}

		// Check if index is valid
		if (index >= this->getSize()) {
			throw std::out_of_range("Index out of range in getNodeByIndex");
		}

		std::shared_ptr<Node<T>> tnode;

		// Optimize traversal direction based on which end is closer
		if (index < this->getSize() / 2) {
			// Start from front for indices in the first half
			tnode = this->front;
			for (size_t i = 0; i < index; i++) {
				tnode = tnode->getRight();
			}
		} else {
			// Start from back for indices in the second half
			tnode = this->back;
			for (size_t i = this->getSize() - 1; i > index; i--) {
				tnode = tnode->getLeft();
			}
		}

		return tnode;
	}

public:

	/**
	 * @class Iterator
	 * @brief Iterator implementation for traversing the List.
	 * Provides a standard iterator interface for List traversal,
	 * extending the IteratorBase template with List-specific functionality.
	 */
	class Iterator : public IteratorBase<T> {
	public:

		/**
		 * @brief Default constructor creating an empty iterator.
		 */
		Iterator() : IteratorBase<T>() {}

		/**
		 * @brief Constructor that initializes the iterator with a node pointer.
		 * @param lp Weak pointer to a Node<T> to start iterating from
		 */
		Iterator(std::weak_ptr<Node<T>> lp) : IteratorBase<T>(lp) {}
	};

	/**
	 * @brief Default constructor that initializes an empty list.
	 */
	List() : Collection<T>() {}

	/**
	 * @brief Constructor that initializes a list with a custom comparator.
	 *
	 * @param comparator The comparator function to use for element comparison
	 */
	List(Comparator<T> comparator) : Collection<T>(comparator) {}

	/**
	 * @brief Destructor that cleans up list resources.
	 */
	~List() {
		clear();
	}

	/**
	 * @brief Array subscript operator for accessing elements by index.
	 * @param index The index of the element to access
	 * @return T The element at the specified index
	 * @throws std::out_of_range If an invalid index is requested
	 */
	T operator[](size_t index) {
		return this->at(index);
	}

	/**
	 * @brief Retrieves the data from the list at the given index position
	 * @param index (`size_t`) the index position within the list where the
	 * data is located.
	 * @returns the data element located at the given index
	 * @throws std::out_of_range error if an invalid index is requested
	 */
	T at(size_t index) {
		if (index < 0 or index > this->size) {
			throw std::out_of_range("Invalid list position index requested");
		}

		std::shared_ptr<Node<T>> lp = this->root;

		for (int i = 0; i < index; i++) {
			lp = lp->getRight();
		}

		return lp->getData();
	}

	/**
	 * @brief copies the current list into an array vector and returns it.
	 * @returns a `vector<T>` collection that contains each element of the list
	 */
	std::vector<T> array(void) {
		std::shared_ptr<Node<T>> lp = this->root;
		std::shared_ptr<Node<T>> next;
		std::vector<T> v;

		while (lp) {
			next = lp->getRight();
			v.push_back(lp->getData());
			lp = next;
		}

		return v;
	}

	/**
	 * @brief Retrieves an iterator to the front of the list
	 * @returns A new Iterator object that points to the front of the list
	 */
	Iterator begin() {
		return Iterator(this->front);
	}

	/**
	 * @brief Retrieves an iterator to the back of the list
	 * @returns A new Iterator object that points to the end of the list
	 */
	Iterator end() {
		return Iterator();
	}

	/**
	 * @brief deletes everything from the current list and resets it to its
	 * initialized state.
	 */
	virtual void clear() override {
		std::shared_ptr<Node<T>> lp = this->root;
		std::shared_ptr<Node<T>> next;

		while (lp) {
			next = lp->getRight();
			lp->clear();
			lp.reset();
			lp = next;
		}

		this->root.reset();
		this->front.reset();
		this->back.reset();
		this->size = 0;
	}

	/**
	 * @brief Performs a linear search through list to find the given data
	 * element.
	 */
	virtual Match<T> find(T data) override {
		// TODO: add find() to List
		Match<T> match;
		return match;
	}

	/**
	 * Inserts an element at the specified position in the list.
	 *
	 * @param data The element to insert
	 * @param position The position to insert at (default is BACK)
	 * @throws std::out_of_range If an invalid position is specified
	 */
	virtual void insert(T data, Position position = Position::BACK) override {
		if (position == Position::BACK) {
			this->insert(data, this->size);
		} else if (position == Position::FRONT) {
			this->insert(data, 0);
		} else {
			throw std::out_of_range("Unknown position value on list insert");
		}
	}

	/**
	 * Inserts an element at the specified index in the list.
	 *
	 * @param data The element to insert
	 * @param index The index at which to insert the element
	 * @throws std::out_of_range If an invalid index is specified
	 *
	 * Behavior:
	 * - If list is empty: Creates the first element
	 * - If index >= size: Adds element to the end
	 * - If index == 0: Adds element to the beginning
	 * - Otherwise: Inserts element at the specified position
	 */
	virtual void insert(T data, size_t index) override {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->root == nullptr) {
			// empty list, first value
			this->root = this->front = this->back = node;
		} else if (index >= this->size) {
			// add a new element to the end of the list
			node->setLeft(this->back);
			this->back->setRight(node);
			this->back = node;
		} else if (index == 0) {
			// add a new element to the front of the list
			node->setRight(this->root);
			this->root->setLeft(node);
			this->root = this->front = node;
		} else if (index > 0 and index < this->size) {
			// add a new element to a arbitrary position in the list
			std::shared_ptr<Node<T>> tnode = getNodeByIndex(index);
			if (tnode != nullptr) {
				node->setRight(tnode);
				node->setLeft(tnode->getLeft());
				tnode->getLeft()->setRight(node);
				tnode->setLeft(node);
			}
		} else {
			throw std::out_of_range("Invalid list insert requested");
		}

		this->size++;
	}

	/**
	 * @brief Converts the list to a JSON string representation.
	 * @return std::string JSON representation of the list
	 */
	virtual std::string json() const override {
		return this->str();
	}

	/**
	 * @brief Removes the specified element from the list if it exists.
	 * @param data The element to remove
	 */
	virtual void remove(T data) override {
		// TODO: add remove() to List
	}

	/**
	 * @brief Removes the specified element from the list by its index.
	 * @param index (``)
	 */
	virtual void remove(size_t index) override {
		// TODO: add remove by index to List
	}

	/**
	 * @brief Creates a vector containing all elements in reverse order.
	 * @return std::vector<T> A vector containing copies of all elements in reverse order
	 */
	std::vector<T> reverse() {
		// TODO: add reverse() to List
	}

	/**
	 * @brief Converts the list to a string representation.
	 * @return std::string String representation of the list
	 */
	virtual std::string str() const override {
		std::stringstream ss;
		std::shared_ptr<Node<T>> lp = this->root;
		std::shared_ptr<Node<T>> next;
		std::string comma = "";

		ss << "[";

		while (lp) {
			next = lp->getRight();
			ss << comma << *lp;
			comma = ",";
			lp = next;
		}

		ss << "]";

		return ss.str();
	}
};
}  // namespace ds
