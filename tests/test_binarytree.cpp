#include <testing_base.h>

#include <ds/BinaryTree.hpp>
#include <ds/List.hpp>
#include <ds/TreeNode.hpp>
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

	EXPECT_EQ(bt.size(), 0);
	EXPECT_EQ(bt.height(), 0);
	EXPECT_TRUE(bt.empty());

	bt.insert(1);
	bt.insert(2);
	bt.insert(3);
	bt.insert(4);
	bt += 6;
	bt += 5;
	bt += 7;

	EXPECT_EQ(bt.height(), 3);
	EXPECT_EQ(bt.size(), 7);
}

TEST_F(TestBinaryTree, CopyConstructor) {
	ds::BinaryTree<int> bt1 {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt1.size(), 7);
	EXPECT_EQ(bt1.height(), 3);
	EXPECT_FALSE(bt1.empty());

	ds::BinaryTree<int> bt2(bt1);
	std::vector<int> out;

	bt2.array(out);
	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);
	EXPECT_EQ(out[4], 5);
	EXPECT_EQ(out[5], 6);
	EXPECT_EQ(out[6], 7);

	ds::BinaryTree<int> bt3 = bt2;

	out.clear();
	bt3.array(out);
	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);
	EXPECT_EQ(out[4], 5);
	EXPECT_EQ(out[5], 6);
	EXPECT_EQ(out[6], 7);
}

TEST_F(TestBinaryTree, Traversals) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.size(), 7);
	EXPECT_EQ(bt.height(), 3);
	EXPECT_FALSE(bt.empty());

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

	out.clear();
	bt.breadth([&](auto &node) { out.push_back(node.getData()); });

	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], 2);
	EXPECT_EQ(out[1], 1);
	EXPECT_EQ(out[2], 4);
	EXPECT_EQ(out[3], 3);
	EXPECT_EQ(out[4], 6);
	EXPECT_EQ(out[5], 5);
	EXPECT_EQ(out[6], 7);

	comma = "";
	std::cout << "breadth: ";
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

TEST_F(TestBinaryTree, ToString) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5};
	std::string result = "BinaryTree[size=5, height=2] {1, 2, 3, 4, 5}";

	EXPECT_EQ(bt.size(), 5);
	EXPECT_EQ(bt.str(), result);
	EXPECT_EQ(bt.json(), result);
}

TEST_F(TestBinaryTree, ComparisonOperators) {
	// TODO: add comparison tests to the test bed
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

	m = bt.breadthSearch(4);
	EXPECT_TRUE(m.found());

	m = bt.breadthSearch(1);
	EXPECT_TRUE(m.found());

	m = bt.breadthSearch(7);
	EXPECT_TRUE(m.found());

	m = bt.breadthSearch(999);
	EXPECT_FALSE(m.found());
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

TEST_F(TestBinaryTree, RemoveSpecial) {
	ds::BinaryTree<int> bt {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(bt.size(), 7);
	EXPECT_EQ(bt.height(), 3);
	EXPECT_FALSE(bt.empty());
	EXPECT_EQ(bt.minimum(), 1);
	EXPECT_EQ(bt.maximum(), 7);

	bt.removeFirst();

	EXPECT_EQ(bt.size(), 6);
	EXPECT_EQ(bt.height(), 3);
	EXPECT_FALSE(bt.empty());
	EXPECT_EQ(bt.minimum(), 2);
	EXPECT_EQ(bt.maximum(), 7);

	bt.removeLast();

	EXPECT_EQ(bt.size(), 5);
	EXPECT_EQ(bt.height(), 3);
	EXPECT_FALSE(bt.empty());
	EXPECT_EQ(bt.minimum(), 2);
	EXPECT_EQ(bt.maximum(), 6);
}

TEST_F(TestBinaryTree, RemoveValueLarge) {
	ds::BinaryTree<int> bt {};
	ds::List<int> l {};
	int treeSize {1000};

	for (int i = 0; i < treeSize; i++) {
		l.insert(i);
	}

	l.shuffle();

	for (auto it: l) {
		bt.insert(it);
	}

	EXPECT_EQ(bt.size(), treeSize);
	EXPECT_TRUE(bt.height() >= 10 && bt.height() <= 13);

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

TEST_F(TestBinaryTree, AIComprehensiveTest) {
	// This set of test cases was generated by Claude to exercise
	// the tree structure and ensure all current methods work as expected

	ds::BinaryTree<int> tree;

	// Initial insertions to build basic structure
	tree.insert(50);  // Root node
	tree.insert(25);  // Left child of root
	tree.insert(75);  // Right child of root

	// Test case 1: Insert nodes that cause simple recoloring
	tree.insert(12);  // Left-left grandchild
	tree.insert(37);  // Left-right grandchild

	// Test case 2: Insert nodes that cause single rotations
	tree.insert(6);	  // Left-left-left great-grandchild (causes left rotation)
	tree.insert(87);  // Right-right grandchild (causes right rotation)

	// Test case 3: Insert nodes that cause double rotations
	tree.insert(
		30);  // Left-right-left great-grandchild (causes left-right rotation)
	tree.insert(60);  // Right-left grandchild (causes right-left rotation)

	// Test case 4: Fill in to create deeper tree for removal testing
	tree.insert(3);	  // Deep left path
	tree.insert(18);  // Middle nodes
	tree.insert(40);
	tree.insert(65);
	tree.insert(80);
	tree.insert(95);  // Deep right path

	// Removal testing sequence (in this order to test all cases)
	tree.removeValue(25);  // Remove node with two children (red)
	tree.removeValue(3);   // Remove leaf node (black)
	tree.removeValue(95);  // Remove leaf node with red sibling
	tree.removeValue(50);  // Remove root node
	tree.removeValue(40);  // Remove node with single child
	tree.removeValue(87);  // Remove node that requires rebalancing
	tree.removeValue(6);   // Special case for removal fix-up
	tree.removeValue(75);  // Node that affects tree structure significantly
	tree.removeValue(18);  // Handle case where successor is not direct child

	// Final removals to test empty tree edge case
	tree.removeValue(12);
	tree.removeValue(30);
	tree.removeValue(37);
	tree.removeValue(60);
	tree.removeValue(65);
	tree.removeValue(80);  // Last node in tree
}
