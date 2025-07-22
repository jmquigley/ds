#include <testing_base.h>

#include <ds/GeneralTree.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestGeneralTree : public TestingBase {
public:

	TestGeneralTree() : TestingBase() {}
};

TEST_F(TestGeneralTree, Create) {
	ds::GeneralTree<size_t> gt;
	std::vector<std::string> out;
	std::string key = "a\\b\\c\\d";

	gt.insert(key, 42);

	EXPECT_EQ(gt.size(), 4);
	EXPECT_EQ(gt.height(), 4);

	gt.breadth([&](auto &node) { out.push_back(node.getKey()); });

	EXPECT_EQ(out.size(), 4);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "b");
	EXPECT_EQ(out[2], "c");
	EXPECT_EQ(out[3], "d");
}

TEST_F(TestGeneralTree, BreadthSearch) {
	ds::GeneralTree<size_t> gt {{"a/b/c", 42}, {"d/e/f/g", 24}};
	std::vector<std::string> out;

	EXPECT_EQ(gt.size(), 7);
	EXPECT_EQ(gt.height(), 4);

	gt.breadth([&](auto &node) { out.push_back(node.getKey()); });

	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "d");
	EXPECT_EQ(out[2], "b");
	EXPECT_EQ(out[3], "e");
	EXPECT_EQ(out[4], "c");
	EXPECT_EQ(out[5], "f");
	EXPECT_EQ(out[6], "g");
}
