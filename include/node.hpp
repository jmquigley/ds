#pragma once

#include <uuid/uuid.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "property.hpp"

namespace ds {
template<typename T>
class Node {
	PROPERTY(data, Data, T);
	PROPERTY(id, Id, std::string);
	PROPERTY(left, Left, std::shared_ptr<Node<T>>);
	PROPERTY(parentId, ParentId, std::string);
	PROPERTY(right, Right, std::shared_ptr<Node<T>>);
	PROPERTY(parent, Parent, std::shared_ptr<Node<T>>);

private:

	std::vector<T> children;

	void init() {
		uuid_t uuid;
		char uuidStr[UUID_STR_LEN];

		// Creates a unique identifier for a node
		uuid_generate_random(uuid);
		uuid_unparse(uuid, uuidStr);
		id = uuidStr;
	}

public:

	Node() : parentId(""), parent(nullptr), left(nullptr), right(nullptr) {
		init();
	}

	Node(T data) : Node(nullptr, nullptr, nullptr, data) {}

	Node(Node<T> parent, T data) : Node(parent, nullptr, nullptr, data) {}

	Node(Node<T> *parent, Node<T> *left, Node<T> *right, T data)
		: parent(parent), left(left), right(right), data(data) {
		init();
		if (parent) {
			parentId = parent->getParentId();
		}
	}

	~Node() {}

	Node(Node<T> &node) {
		this->data = node.data;
		this->id = node.id;
		this->parentId = node.parentId;
		this->parent = node.parent;
		this->right = node.right;
		this->left = node.left;
		this->children = node.children;
	}

	friend std::ostream &operator<<(std::ostream &st, const Node<T> &node) {
		return st << node.str();
	}

	void clear() {
		this->id = "";
		this->parentId = "";
		this->parent = nullptr;
		this->right = nullptr;
		this->left = nullptr;
		this->children.clear();
		init();
	}

	std::string str() const {
		std::stringstream ss;

		ss << "{";
		ss << "\"data\":" << data;
		ss << "}";

		return ss.str();
	}
};

template<typename T>
class NodeBuilder {
private:

	Node<T> node;

public:

	NodeBuilder &withData(T data) {
		node.setData(data);
		return *this;
	}

	NodeBuilder &withId(std::string id) {
		node.setId(id);
		return *this;
	}

	NodeBuilder &withParentId(std::string parentId) {
		node.setParentId(parentId);
		return *this;
	}

	NodeBuilder &withParent(std::shared_ptr<Node<T>> parent) {
		node.setParent(parent);
	}

	NodeBuilder &withRight(std::shared_ptr<Node<T>> right) {
		node.setRight(right);
	}

	NodeBuilder &withLeft(std::shared_ptr<Node<T>> left) {
		node.setLeft(left);
	}

	Node<T> build() {
		return node;
	}
};
}  // namespace ds
