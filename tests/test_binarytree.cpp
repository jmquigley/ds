#include <iostream>
#include <string>
#include <vector>

#include "binarytree.hpp"
#include "testing_base.h"

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

	std::vector<int> out;
	std::string comma;

	out = bt.inorder();
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

	out = bt.postorder();
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

	out = bt.preorder();
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
}
