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

	std::vector<int> out;
	std::string comma;

	out = bt.inorder();
	EXPECT_EQ(out.size(), 3);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);

	comma = "";
	std::cout << "inorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;

	out = bt.postorder();
	EXPECT_EQ(out.size(), 3);
	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 3);
	EXPECT_EQ(out[2], 2);

	comma = "";
	std::cout << "postorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;

	out = bt.preorder();
	EXPECT_EQ(out.size(), 3);
	EXPECT_EQ(out[0], 2);
	EXPECT_EQ(out[1], 1);
	EXPECT_EQ(out[2], 3);

	comma = "";
	std::cout << "preorder: ";
	for (auto it: out) {
		std::cout << comma << it;
		comma = ",";
	}
	std::cout << std::endl;
}
