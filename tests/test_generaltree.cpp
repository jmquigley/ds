#include <ds/str.h>
#include <testing_base.h>

#include <ds/GeneralTree.hpp>
#include <ds/Path.hpp>
#include <ds/constants.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestGeneralTree : public TestingBase {
public:

	TestGeneralTree() : TestingBase() {}
};

TEST_F(TestGeneralTree, Create) {
	/*
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
	*/
}

/*
TEST_F(TestGeneralTree, Breadth) {
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
*/

/* TODO: add depth test for GeneralTree

TEST_F(TestGeneralTree, Depth) {
	ds::GeneralTree<size_t> gt {
		{"a/b/d", 42}, {"a/b/e", 24}, {"a/c/f", 12}, {"a/c/g", 13}};
	std::vector<std::string> out;

	EXPECT_EQ(gt.size(), 7);
	EXPECT_EQ(gt.height(), 3);

	gt.depth([&](auto &node) { out.push_back(node.getKey()); });

	EXPECT_EQ(out.size(), 7);
	EXPECT_EQ(out[0], "a");
	EXPECT_EQ(out[1], "b");
	EXPECT_EQ(out[2], "d");
	EXPECT_EQ(out[3], "e");
	EXPECT_EQ(out[4], "c");
	EXPECT_EQ(out[5], "f");
	EXPECT_EQ(out[6], "g");
}

TEST_F(TestGeneralTree, FindByPath) {
	ds::GeneralTree<std::string> gt {{"a/b/c", "a"},   {"a/b/d", "d"},
									 {"a/b/z", "b"},   {"d/e/f/g", "e"},
									 {"d/e/f/h", "c"}, {"d/e/f/i", "f"}};
	std::vector<std::string> out;

	EXPECT_EQ(gt.size(), 11);
	EXPECT_EQ(gt.height(), 4);

	gt.breadth([&](auto &node) {
		out.push_back(node.getPath().str());
		std::cout << node.getPath().str() << std::endl;
	});

	ds::Path path("a", "b", "d");
	auto match = gt.findByPath(path);
	EXPECT_TRUE(match.found());

	path.clear();

atch = gt.findByPath(path);
	EXPECT_FALSE(match.found());

	match = gt.findByPath("a/b/c");
	EXPECT_TRUE(match.found());
}
*/
