#pragma once

#include <BaseIterator.hpp>
#include <Collection.hpp>
#include <Iterable.hpp>
#include <cstddef>
#include <exception>
#include <helpers.hpp>
#include <limits>
#include <property.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace ds {

/**
 * @class List
 * @brief A generic doubly linked list class.
 *
 * TODO: add expanded description and code sample for a list
 *
 * @tparam T The type of data stored within the list.
 */
template<typename T>
class List : public Collection<T, Node>, public Iterable<T, Node> {
protected:

	/**
	 * @brief adds a new node to the end of the list
	 * @param node (`std::shared_ptr<Node<T>>`) the node to add to the end
	 */
	void addBack(std::shared_ptr<Node<T>> node) {
		// add a new element to the end of the list
		node->setLeft(this->_back.lock());
		this->_back.lock()->setRight(node);
		this->_back = node;
	}

	/**
	 * @brief adds a new node to the front of the list
	 * @param node (`std::shared_ptr<Node<T>>`) the node to add to the front
	 */
	void addFront(std::shared_ptr<Node<T>> node) {
		// add a new element to the front of the list
		node->setRight(this->_root);
		this->_root->setLeft(node);
		this->_root = node;
		this->_front = node;
	}

	/**
	 * @brief Retrieves the node at the specified index.
	 * @param index (`size_t`) The index of the node to retrieve, or a
	 * Position enum value
	 * @return std::shared_ptr<Node<T>> Pointer to the node at the specified index
	 */
	std::shared_ptr<Node<T>> getNodeByIndex(size_t index) {
		std::shared_ptr<Node<T>> tnode;

		// Optimize traversal direction based on which end is closer
		if (index < (this->_size / 2)) {
			// Start from front for indices in the first half
			tnode = this->getFront().lock();
			for (size_t i = 0; i < index; i++) {
				tnode = tnode->getRight();
			}
		} else {
			// Start from back for indices in the second half
			tnode = this->getBack().lock();
			for (size_t i = this->_size - 1; i > index; i--) {
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
	class Iterator : public BaseIterator<T, Node> {
	public:

		/**
		 * @brief Default constructor creating an empty iterator.
		 */
		Iterator() : BaseIterator<T, Node>() {}

		/**
		 * @brief Constructor that initializes the iterator with a node pointer.
		 * @param lp Weak pointer to a Node<T> to start iterating from
		 */
		Iterator(std::weak_ptr<Node<T>> lp) : BaseIterator<T, Node>(lp) {}
	};

	/**
	 * @brief Default constructor that initializes an empty list.
	 */
	List() : Collection<T, Node>() {}

	/**
	 * @brief Constructor that initializes a list with a custom comparator.
	 *
	 * @param comparator The comparator function to use for element comparison
	 */
	List(Comparator<T> comparator) : Collection<T, Node>(comparator) {}

	/**
	 * @brief a List copy constructor
	 * @param list (`List &`) the list object to copy
	 */
	List(List<T> &list) {
		for (auto it: list) {
			this->insert(it);
		}
	}

	/**
	 * @brief Constructor that takes an initializer_list to insert values into
	 * the collection.
	 *
	 * @param il (`std::initializer_list`) a list of values to see the list
	 */
	List(std::initializer_list<T> il) : Collection<T, Node>() {
		for (auto it: il) {
			this->insert(it);
		}
	}

	/**
	 * @brief Destructor that cleans up list resources.
	 */
	~List() {
		this->clear();
	}

	/**
	 * @brief Overloads the stream insertion operator for List objects.
	 *
	 * Allows printing a List object directly to an output stream, using its
	 * `str()` method for representation.
	 *
	 * @param st (`std::ostream`) the output stream
	 * @param list (`List<T> &`) the List object to print
	 * @returns a reference to the `std::ostream` object
	 */
	friend std::ostream &operator<<(std::ostream &st, const List<T> &list) {
		return st << list.str();
	}

	/**
	 * @brief Retrieves the data from the list at the given index position
	 * @param index (`size_t`) the index position within the list where the
	 * data is located.
	 * @returns the data element located at the given index
	 * @throws std::out_of_range error if an invalid index is requested
	 */
	T at(size_t index) const override {
		if (index < 0 or index >= this->_size) {
			throw std::out_of_range("Invalid list position index requested");
		}

		std::shared_ptr<Node<T>> lp = this->_root;

		for (size_t i = 0; i < index; i++) {
			lp = lp->getRight();
		}

		return lp->getData();
	}

	/**
	 * @brief copies the current list into an array vector and returns it.
	 * @returns a `vector<T>` collection that contains each element of the list
	 */
	std::vector<T> array(void) {
		std::shared_ptr<Node<T>> lp = this->_root;
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
	inline Iterator begin() const {
		return Iterator(this->_front);
	}

	/**
	 * @brief Retrieves an iterator to the back of the list
	 * @returns A new Iterator object that points to the back of the list
	 */
	inline Iterator rbegin() const {
		return Iterator(this->_back);
	}

	/**
	 * @brief deletes everything from the current list and resets it to its
	 * initialized state.
	 */
	virtual void clear() override {
		std::shared_ptr<Node<T>> lp = this->_root;
		std::shared_ptr<Node<T>> next;

		while (lp) {
			next = lp->getRight();
			lp->clear();
			lp.reset();
			lp = next;
		}

		this->_root.reset();
		this->_front.reset();
		this->_back.reset();
		this->_size = 0;
	}

	/**
	 * @brief Checks if a `T` data element exists within the list
	 * @returns true if the data element exists in the list, otherwise false.
	 */
	inline bool contains(T data) const override {
		Match<T, Node> match = find(data);
		return match.found();
	}

	/**
	 * @brief Retrieves an iterator to the back of the list
	 * @returns A new Iterator object that points to the end of the list
	 */
	inline Iterator end() const {
		return Iterator();
	}

	/**
	 * @brief Retrieves an iterator to the front of the list
	 * @returns A new Iterator object that points to the front of the list
	 */
	inline Iterator rend() const {
		return Iterator();
	}

	/**
	 * @brief Performs a linear search through list to find the given data
	 * element.
	 * @returns a `Match<T>` object that contains information about the `Node`
	 * that was found in the search.
	 */
	virtual Match<T, Node> find(T data) const override {
		size_t index = 0;
		std::shared_ptr<Node<T>> lp = this->_root;
		Match<T, Node> match;
		std::shared_ptr<Node<T>> next;

		while (lp) {
			if (this->comparator(lp->getData(), data) == 0) {
				match.setData(data);
				match.setFound(true);
				match.setIndex(index);
				match.setRef(lp);

				return match;
			}

			index++;
			lp = lp->getRight();
		}

		return match;
	}

	/**
	 * @brief Insert the given data into a collection at back of the collection
	 * @param data The element to insert
	 */
	virtual void insert(T data) override {
		this->insert(data, Position::BACK);
	}

	/**
	 * Inserts an element at the specified position in the list.
	 *
	 * @param data The element to insert
	 * @param position The position to insert at (default is BACK)
	 */
	void insert(T data, Position position) {
		if (position == Position::BACK) {
			this->insert(data, this->_size);
		} else if (position == Position::FRONT) {
			this->insert(data, 0);
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
	void insert(T data, size_t index) {
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(data);

		if (this->_root == nullptr) {
			// empty list, first value
			this->_root = node;
			this->_front = this->_back = node;
		} else if (index >= this->_size) {
			addBack(node);
		} else if (index == 0) {
			addFront(node);
		} else {
			// add a new element to a arbitrary position in the list
			std::shared_ptr<Node<T>> tnode = getNodeByIndex(index);
			if (tnode != nullptr) {
				node->setRight(tnode);
				node->setLeft(tnode->getLeft());
				tnode->getLeft()->setRight(node);
				tnode->setLeft(node);
			}
		}

		this->_size++;
	}

	/**
	 * @brief Removes the specified element from the list by its index.
	 * @param index (`size_t`) the position within the list to remove
	 * @param tnode (`std::shared_ptr<Node<T>>`) a reference to the node that will
	 * be deleted.  This is a convenience reference to speed up the search if it has
	 * already been performed.
	 * @returns the T value that was removed from the list
	 * @throws an out_of_range exception if the requested index is invalid
	 */
	virtual T removeAt(size_t index, std::shared_ptr<Node<T>> tnode = nullptr) override {
		if (this->_size == 0) {
			throw std::out_of_range("Cannot remove item from an empty list");
		}

		if (index == 0) {
			// Remove the root node
			tnode = this->_root;
			this->_root = this->_root->getRight();

			if (this->_root) {
				this->_root->setLeft(nullptr);
			}

			this->_front = this->_root;
		} else if (index >= this->_size - 1) {
			// Removes the last node in the list
			tnode = this->_back.lock();
			this->_back = this->_back.lock()->getLeft();
			this->_back.lock()->setRight(nullptr);
		} else {
			if (tnode == nullptr) {
				tnode = this->getNodeByIndex(index);
			}

			tnode->getRight()->setLeft(tnode->getLeft());
			tnode->getLeft()->setRight(tnode->getRight());
		}

		T data = tnode->getData();
		tnode.reset();
		this->_size--;

		return data;
	}

	/**
	 * @brief Removes the first instance of the given value from the list.
	 * @param value (`T`) a data value to find and remove from the list
	 * @returns the T value that was removed from the list
	 */
	virtual T removeValue(T value) override {
		if (this->_size == 0) {
			throw std::out_of_range("Invalid list position requested for remove");
		}

		Match<T, Node> match = find(value);
		if (match.found()) {
			return removeAt(match.getIndex(), match.getRef().lock());
		}

		std::stringstream ss;
		ss << "Invalid value selected for remove (" << value << ")";
		throw std::range_error(ss.str());
	}

	/**
	 * @brief Creates a vector containing all elements in reverse order.
	 * @return std::vector<T> A vector containing copies of all elements in reverse order
	 */
	std::vector<T> reverse() {
		std::shared_ptr<Node<T>> lp = this->_back.lock();
		std::shared_ptr<Node<T>> previous;
		std::vector<T> v;

		while (lp) {
			previous = lp->getLeft();
			v.push_back(lp->getData());
			lp = previous;
		}

		return v;
	}

	/**
	 * @brief Converts the list to a string representation.
	 * @return std::string String representation of the list
	 */
	virtual std::string str() const override {
		std::stringstream ss;
		std::shared_ptr<Node<T>> lp = this->_root;
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
