/**
 * @file list.hpp
 * @brief Defines a doubly linked list data structure collection.
 */

#pragma once

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

	std::shared_ptr<Node<T>> getNodeByIndex(size_t idx) {
		std::shared_ptr<Node<T>> tnode = this->root;

		if (idx == as_integer(Position::BACK)) {
			idx = this->getSize() - 1;
		} else if (idx == as_integer(Position::FRONT)) {
			idx = 0;
		}

		if (tnode) {
			for (size_t i = 0; i < idx; i++) {
				if (tnode) {
					tnode = tnode->getRight();
				}
			}
		}

		return tnode;
	}

public:

	class Iterator : public IteratorBase<T> {
	public:

		Iterator() : IteratorBase<T>() {}

		Iterator(std::weak_ptr<Node<T>> lp) : IteratorBase<T>(lp) {}
	};

	List() : Collection<T>() {}

	List(Comparator<T> comparator) : Collection<T>(comparator) {}

	~List() {
		clear();
	}

    T operator[](size_t index) {
        return this->at(index);
    }

    /**
     * @brief Retrieves the data from the list at the given index position
     * @param pos (`size_t`) the index position within the list where the
     * data is located.
     * @returns the data element located at the given index
     * @throws std::runtime_error if an invalid index is requested
     */
	T at(size_t index) {
		if (index < 0 or index > this->size) {
			throw std::runtime_error("Invalid list position index requested");
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

	virtual void insert(T data, ssize_t idx = -1, Position position = Position::BACK) override {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->root == nullptr) {
			// empty list, first value
			this->root = this->front = this->back = node;
		} else if (idx == as_integer(Position::BACK)) {
			// add a new element to the end of the list
			node->setLeft(this->back);
			this->back->setRight(node);
			this->back = node;
		} else if (idx == as_integer(Position::FRONT)) {
			// add a new element to the front of the list
			node->setRight(this->root);
			this->root->setLeft(node);
			this->root = this->front = node;
		} else if (idx >= 0) {
			// add a new element to a arbitrary position in the list
			std::shared_ptr<Node<T>> tnode = getNodeByIndex(idx);
			if (tnode != nullptr) {
				node->setRight(tnode);
				node->setLeft(tnode->getLeft());
				tnode->getLeft()->setRight(node);
				tnode->setLeft(node);
			}
		} else {
			throw std::runtime_error("Invalid list insert requested");
		}

		this->size++;
	}

	virtual std::string json() const override {
		// TODO: add json() to List
		return "";
	}

	virtual void remove(T data) override {
		// TODO: add remove() to List
	}

	std::vector<T> reverse() {
		// TODO: add reverse() to List
	}

	virtual std::string str() const override {
		// TODO: add str() to List
		return "";
	}
};
}  // namespace ds
