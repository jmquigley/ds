#include <testing_base.h>

#include <BinaryTree.hpp>
#include <List.hpp>
#include <TreeNode.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class TestBinaryTree : public TestingBase {
public:

	TestBinaryTree() : TestingBase() {}

	void showInorder(ds::BinaryTree<int> &bt) {
		std::vector<int> out;
		std::string comma;

		bt.inorder([&](auto &node) { out.push_back(node.getData()); });

		comma = "";
		std::cout << "show->inorder: ";
		for (auto it: out) {
			std::cout << comma << it;
			comma = ",";
		}
		std::cout << std::endl;
	}
};

TEST_F(TestBinaryTree, CreateBinaryTree) {
	ds::BinaryTree<int> bt;

	bt.insert(1);
	bt.insert(2);
	bt.insert(3);
	bt.insert(4);
	bt.insert(6);
	bt.insert(5);
	bt.insert(7);

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);

	std::vector<int> out;
	std::string comma;

	bt.array(out);
	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);
	EXPECT_EQ(out[4], 5);
	EXPECT_EQ(out[5], 6);
	EXPECT_EQ(out[6], 7);

	std::vector<int> out2 = bt.array();
	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);
	EXPECT_EQ(out[4], 5);
	EXPECT_EQ(out[5], 6);
	EXPECT_EQ(out[6], 7);

	comma = "";
	std::cout << "inorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;

	out.clear();
	bt.postorder([&](auto &node) { out.push_back(node.getData()); });

	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 3);
	EXPECT_EQ(out[2], 5);
	EXPECT_EQ(out[3], 7);
	EXPECT_EQ(out[4], 6);
	EXPECT_EQ(out[5], 4);
	EXPECT_EQ(out[6], 2);

	comma = "";
	std::cout << "postorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;

	out.clear();
	bt.preorder([&](auto &node) { out.push_back(node.getData()); });

	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 2);
	EXPECT_EQ(out[1], 1);
	EXPECT_EQ(out[2], 4);
	EXPECT_EQ(out[3], 3);
	EXPECT_EQ(out[4], 6);
	EXPECT_EQ(out[5], 5);
	EXPECT_EQ(out[6], 7);

	comma = "";
	std::cout << "preorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;

	out.clear();
	bt.reverseorder([&](auto &node) { out.push_back(node.getData()); });

	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 7);
	EXPECT_EQ(out[1], 6);
	EXPECT_EQ(out[2], 5);
	EXPECT_EQ(out[3], 4);
	EXPECT_EQ(out[4], 3);
	EXPECT_EQ(out[5], 2);
	EXPECT_EQ(out[6], 1);

	comma = "";
	std::cout << "reverseorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;
}

TEST_F(TestBinaryTree, InitializerListAndOperator) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5};

	EXPECT_EQ(bt.size(), 5);
	EXPECT_EQ(bt[0], 1);
	EXPECT_EQ(bt[1], 2);
	EXPECT_EQ(bt[2], 3);
	EXPECT_EQ(bt[3], 4);
	EXPECT_EQ(bt[4], 5);

	bt = {6, 7, 8, 9, 10};

	EXPECT_EQ(bt.size(), 5);
	EXPECT_EQ(bt[0], 6);
	EXPECT_EQ(bt[1], 7);
	EXPECT_EQ(bt[2], 8);
	EXPECT_EQ(bt[3], 9);
	EXPECT_EQ(bt[4], 10);
}

TEST_F(TestBinaryTree, Search) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);

	ds::Match<int, ds::TreeNode> m;

	m = bt.find(4);
	EXPECT_TRUE(m.found());

	m = bt.find(999);
	EXPECT_FALSE(m.found());

	EXPECT_TRUE(bt.contains(5));
	EXPECT_FALSE(bt.contains(999));
}

TEST_F(TestBinaryTree, At) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);

	EXPECT_EQ(bt.at(0), 1);
	EXPECT_EQ(bt.at(1), 2);
	EXPECT_EQ(bt.at(2), 3);
	EXPECT_EQ(bt.at(3), 4);
	EXPECT_EQ(bt.at(4), 5);
	EXPECT_EQ(bt.at(5), 6);
	EXPECT_EQ(bt.at(6), 7);

	EXPECT_EQ(bt[0], 1);
	EXPECT_EQ(bt[1], 2);
	EXPECT_EQ(bt[2], 3);
	EXPECT_EQ(bt[3], 4);
	EXPECT_EQ(bt[4], 5);
	EXPECT_EQ(bt[5], 6);
	EXPECT_EQ(bt[6], 7);

	EXPECT_THROW(bt.at(999), std::out_of_range);
}

TEST_F(TestBinaryTree, RemoveValue) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);

	bt.removeValue(7);
	showInorder(bt);

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 6);

	EXPECT_EQ(bt[0], 1);
	EXPECT_EQ(bt[1], 2);
	EXPECT_EQ(bt[2], 3);
	EXPECT_EQ(bt[3], 4);
	EXPECT_EQ(bt[4], 5);
	EXPECT_EQ(bt[5], 6);

	bt.removeValue(3);

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 5);

	EXPECT_EQ(bt[0], 1);
	EXPECT_EQ(bt[1], 2);
	EXPECT_EQ(bt[2], 4);
	EXPECT_EQ(bt[3], 5);
	EXPECT_EQ(bt[4], 6);

	bt.removeValue(2);

	EXPECT_EQ(bt.height(), 2);
	EXPECT_EQ(bt.size(), 4);

	EXPECT_EQ(bt[0], 1);
	EXPECT_EQ(bt[1], 4);
	EXPECT_EQ(bt[2], 5);
	EXPECT_EQ(bt[3], 6);

	bt.removeValue(1);

	EXPECT_EQ(bt.height(), 2);
	EXPECT_EQ(bt.size(), 3);

	EXPECT_EQ(bt[0], 4);
	EXPECT_EQ(bt[1], 5);
	EXPECT_EQ(bt[2], 6);
}

TEST_F(TestBinaryTree, RemoveValueLarge) {
	ds::BinaryTree<int> bt {};
	ds::List<int> l {};
	int treeSize {10000};

	for (int i = 0; i < treeSize; i++) {
		l.insert(i);
	}

	l.shuffle();

	for (auto it: l) {
		bt.insert(it);
	}

	EXPECT_EQ(bt.size(), treeSize);
	EXPECT_EQ(bt.height(), 15);

	for (int i = treeSize - 1; i >= 0; i--) {
		bt.removeValue(i);
	}

	EXPECT_EQ(bt.size(), 0);
	EXPECT_EQ(bt.height(), 0);
}

TEST_F(TestBinaryTree, RemoveValueBad) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);

	EXPECT_THROW(bt.removeValue(999), std::invalid_argument);
	EXPECT_THROW(bt.removeAt(999), std::out_of_range);
}

TEST_F(TestBinaryTree, RemoveAt) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);

	bt.removeAt(6);
	showInorder(bt);

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 6);

	EXPECT_EQ(bt[0], 1);
	EXPECT_EQ(bt[1], 2);
	EXPECT_EQ(bt[2], 3);
	EXPECT_EQ(bt[3], 4);
	EXPECT_EQ(bt[4], 5);
	EXPECT_EQ(bt[5], 6);

	bt.removeAt(0);

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 5);

	EXPECT_EQ(bt[0], 2);
	EXPECT_EQ(bt[1], 3);
	EXPECT_EQ(bt[2], 4);
	EXPECT_EQ(bt[3], 5);
	EXPECT_EQ(bt[4], 6);
}

TEST_F(TestBinaryTree, RemoveFromEmpty) {
	ds::BinaryTree<int> bt {};

	EXPECT_EQ(bt.height(), 0);
	EXPECT_EQ(bt.size(), 0);

	EXPECT_THROW(bt.removeValue(0), std::invalid_argument);
	EXPECT_THROW(bt.removeAt(0), std::out_of_range);
}
