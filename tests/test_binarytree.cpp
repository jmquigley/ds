#include <testing_base.h>

#include <BinaryTree.hpp>
#include <TreeNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestBinaryTree : public TestingBase {
public:

	TestBinaryTree() : TestingBase() {}
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
