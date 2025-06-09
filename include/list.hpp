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
 *
 * @tparam T The type of data stored within the list.
 */
template<typename T>
class List : public Collection<T>, public Iterable<T> {
private:

	std::shared_ptr<Node<T>> getNodeByIndex(size_t idx) {
		std::shared_ptr<Node<T>> tnode = this->root;

		if (idx == as_integer(Position::BACK)) {
			idx = this->getLength() - 1;
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

		Iterator(std::shared_ptr<Node<T>> lp) : IteratorBase<T>(lp) {}
	};

	List() : Collection<T>() {}

	List(Comparator<T> comparator) : Collection<T>(comparator) {}

	~List() {}

	T at(size_t pos) {
		// TODO: add at() to List
	}

	std::vector<T> array(void) {
		// TODO: add array() to List
	}

	Iterator begin() {
		return Iterator(this->first);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	virtual void clear() override {
		// TODO: add clear() to List
	}

	virtual Node<T> find(T data) override {
		// TODO: add find() to List
		Node<T> node;
		return node;
	}

	virtual void insert(T data, ssize_t idx = -1, Position position = Position::BACK) override {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->root == nullptr) {
			// empty list, first value
			this->root = this->first = this->last = node;
		} else if (idx == as_integer(Position::BACK)) {
			// add a new element to the end of the list
			node->setLeft(this->last);
			this->last->setRight(node);
			this->last = node;
		} else if (idx == as_integer(Position::FRONT)) {
			// add a new element to the front of the list
			node->setRight(this->root);
			this->root->setLeft(node);
			this->root = this->first = node;
		} else if (idx >= 0) {
			// add a new element to a arbitrary position in the list
			std::shared_ptr<Node<T>> tnode = getNodeByIndex(idx);
			if (tnode != nullptr) {
				node->setRight(tnode);
				node->setLeft(tnode->getLeft());
				tnode->getLeft()->setRight(node);
				tnode->setLeft(node);
			}
		}

		this->length++;
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
