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

	/*
		bt.insert(2);
		bt.insert(1);
		bt.insert(3);

		std::vector<int> out = bt.postorder();

		for (auto it: out) {
			std::cout << it << std::endl;
		}
	*/
}
