#pragma once

#include <ds/BaseTree.hpp>
#include <ds/GeneralTreeNode.hpp>
#include <ds/Match.hpp>
#include <string>

namespace ds {

template<typename T>
class GeneralTree : public BaseTree<T, GeneralTreeNode> {
private:

	std::shared_ptr<GeneralTreeNode<T>> newNode(
		std::string key, T data, std::shared_ptr<GeneralTreeNode<T>> &parent) {
		std::shared_ptr<GeneralTreeNode<T>> node;
		GeneralTreeNodeBuilder<T> builder;

		node = builder.withKey(key).withData(data).withParent(parent).build();

		return node;
	}

public:

	GeneralTree() : BaseTree<T, GeneralTreeNode>() {}

	GeneralTree(Comparator<T> &comparator)
		: BaseTree<T, GeneralTreeNode>(comparator) {}

	virtual ~GeneralTree() {
		this->clear();
	}

	template<typename Callback>
	void breadth(Callback callback) const {
		// TODO: implement breadth traversal through the tree
	}

	Match<T, GeneralTreeNode> breadthSearch(std::string key) const {
		// TODO: implement breadthSearch for GeneralTree
	}

	void clear() {
		// TODO: implement clear() for GeneralTree
	}

	bool contains(std::string key) const {
		// TODO: implement contains() for GeneralTree
		return false;
	}

	Match<T, GeneralTreeNode> find(std::string key) const {
		// TODO: implmenet find() for GeneralTree
		Match<T, GeneralTreeNode> match;
		return match;
	}

	virtual size_t height() const {
		// TODO: implement height() for GeneralTree
		return 0;
	}

	std::string json() const {
		// TODO: implement json() for GeneralTree
		return "";
	}

	void insert(std::string key, T data) {
		// TODO: implement insert() for GeneralTree
	}

	T remove(std::string key) {
		// TODO: implement remove() for GeneralTree
		T data {};
		return data;
	}

	std::string str() const {
		// TODO: implement str() for GeneralTree
		return "";
	}
};

}  // namespace ds
