#include <testing_base.h>

#include <GeneralTreeNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestGeneralTreeNode : public TestingBase {
public:

	TestGeneralTreeNode() : TestingBase() {}
};

TEST_F(TestGeneralTreeNode, Create) {
	ds::GeneralTreeNode<int> gtn("a", 42);

	EXPECT_EQ(gtn.data(), 42);
	EXPECT_EQ(gtn.parent(), nullptr);

	gtn.addChild("a1", 1);
	gtn.addChild("b1", 2);
	gtn.addChild("a2", 3);

	EXPECT_EQ(gtn.totalChildren(), 3);

	std::vector<std::shared_ptr<ds::GeneralTreeNode<int>>> out =
		gtn.getChildren();

	EXPECT_EQ(out.size(), 3);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch1 = gtn.getChild("a1");
	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0], ch1);
	EXPECT_EQ(out[0]->data(), 1);
	EXPECT_EQ(out[0]->parent(), &gtn);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch2 = gtn.getChild("a2");
	EXPECT_EQ(out[1]->key(), "a2");
	EXPECT_EQ(out[1], ch2);
	EXPECT_EQ(out[1]->data(), 3);
	EXPECT_EQ(out[1]->parent(), &gtn);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch3 = gtn.getChild("b1");
	EXPECT_EQ(out[2]->key(), "b1");
	EXPECT_EQ(out[2], ch3);
	EXPECT_EQ(out[2]->data(), 2);
	EXPECT_EQ(out[2]->parent(), &gtn);

	gtn.removeChild("a2");

	EXPECT_EQ(gtn.totalChildren(), 2);

	out = gtn.getChildren();

	ch1 = gtn.getChild("a1");
	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0], ch1);
	EXPECT_EQ(out[0]->data(), 1);
	EXPECT_EQ(out[0]->parent(), &gtn);

	ch3 = gtn.getChild("b1");
	EXPECT_EQ(out[1]->key(), "b1");
	EXPECT_EQ(out[1], ch3);
	EXPECT_EQ(out[1]->data(), 2);
	EXPECT_EQ(out[1]->parent(), &gtn);

	gtn.clear();

	EXPECT_EQ(gtn.totalChildren(), 0);
	EXPECT_EQ(gtn.key(), "");
	EXPECT_EQ(gtn.parent(), nullptr);
};

TEST_F(TestGeneralTreeNode, Comparisons) {
	ds::GeneralTreeNode<int> gtn1("a", 1);
	ds::GeneralTreeNode<int> gtn2("b", 2);

	EXPECT_FALSE(gtn1 == gtn2);
	EXPECT_TRUE(gtn1 == gtn1);

	EXPECT_FALSE(gtn1 != gtn1);
	EXPECT_TRUE(gtn1 != gtn2);
}
