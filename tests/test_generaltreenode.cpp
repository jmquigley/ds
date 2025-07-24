#include <testing_base.h>

#include <ds/GeneralTreeNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestGeneralTreeNode : public TestingBase {
public:

	TestGeneralTreeNode() : TestingBase() {}
};

TEST_F(TestGeneralTreeNode, Create) {
	std::shared_ptr<ds::GeneralTreeNode<int>> gtn =
		std::make_shared<ds::GeneralTreeNode<int>>("a", 42, "a\\");

	EXPECT_EQ(gtn->data(), 42);
	EXPECT_EQ(gtn->parent().use_count(), 0);

	gtn->addChild("a1", 1, "a\\a1");
	gtn->addChild("b1", 2, "a\\b1");
	gtn->addChild("a2", 3, "a\\a2");

	EXPECT_EQ(gtn->totalChildren(), 3);

	std::vector<std::shared_ptr<ds::GeneralTreeNode<int>>> out =
		gtn->getChildren();

	EXPECT_EQ(out.size(), 3);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch1 = gtn->getChild("a1");
	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0], ch1);
	EXPECT_EQ(out[0]->data(), 1);
	EXPECT_EQ(out[0]->path(), "a\\a1");
	EXPECT_EQ(out[0]->parent(), gtn);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch2 = gtn->getChild("a2");
	EXPECT_EQ(out[1]->key(), "a2");
	EXPECT_EQ(out[1], ch2);
	EXPECT_EQ(out[1]->data(), 3);
	EXPECT_EQ(out[1]->path(), "a\\a2");
	EXPECT_EQ(out[1]->parent(), gtn);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch3 = gtn->getChild("b1");
	EXPECT_EQ(out[2]->key(), "b1");
	EXPECT_EQ(out[2], ch3);
	EXPECT_EQ(out[2]->data(), 2);
	EXPECT_EQ(out[2]->path(), "a\\b1");
	EXPECT_EQ(out[2]->parent(), gtn);

	EXPECT_TRUE(gtn->hasChild("a1"));
	EXPECT_FALSE(gtn->hasChild("zz"));

	gtn->removeChild("a2");

	EXPECT_EQ(gtn->totalChildren(), 2);

	out = gtn->getChildren();

	ch1 = gtn->getChild("a1");
	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0], ch1);
	EXPECT_EQ(out[0]->data(), 1);
	EXPECT_EQ(out[0]->path(), "a\\a1");
	EXPECT_EQ(out[0]->parent(), gtn);

	ch3 = gtn->getChild("b1");
	EXPECT_EQ(out[1]->key(), "b1");
	EXPECT_EQ(out[1], ch3);
	EXPECT_EQ(out[1]->data(), 2);
	EXPECT_EQ(out[1]->path(), "a\\b1");
	EXPECT_EQ(out[1]->parent(), gtn);

	gtn->clear();

	EXPECT_EQ(gtn->totalChildren(), 0);
	EXPECT_EQ(gtn->key(), "");
	EXPECT_EQ(gtn->parent(), nullptr);
};

TEST_F(TestGeneralTreeNode, Comparisons) {
	ds::GeneralTreeNode<int> gtn1("a", 1, "a");
	ds::GeneralTreeNode<int> gtn2("b", 2, "b");

	EXPECT_FALSE(gtn1 == gtn2);
	EXPECT_TRUE(gtn1 == gtn1);

	EXPECT_FALSE(gtn1 != gtn1);
	EXPECT_TRUE(gtn1 != gtn2);
}

TEST_F(TestGeneralTreeNode, WithBuilder) {
	std::shared_ptr<ds::GeneralTreeNode<int>> gtn;
	std::shared_ptr<ds::GeneralTreeNode<int>> parent =
		std::make_shared<ds::GeneralTreeNode<int>>("p", 42, "p\\");
	ds::GeneralTreeNodeBuilder<int> builder;

	gtn = builder.withData(1)
			  .withKey("a")
			  .withPath("a\\")
			  .withChild("a1", 1, "a\\a1")
			  .withChild("a2", 3, "a\\a2")
			  .withChild("b1", 2, "a\\b1")
			  .withParent(parent)
			  .build();

	std::vector<std::shared_ptr<ds::GeneralTreeNode<int>>> out =
		gtn->getChildren();

	EXPECT_EQ(gtn->totalChildren(), 3);
	EXPECT_EQ(gtn->key(), "a");
	EXPECT_EQ(gtn->parent()->key(), "p");
	EXPECT_EQ(gtn->parent()->data(), 42);
	EXPECT_EQ(gtn->path(), "a\\");
	EXPECT_EQ(gtn->parent()->parent(), nullptr);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch1 = gtn->getChild("a1");

	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0]->key(), ch1->key());
	EXPECT_EQ(out[0]->data(), 1);
	EXPECT_EQ(out[0]->data(), ch1->data());
	EXPECT_EQ(out[0]->path(), "a\\a1");
	EXPECT_EQ(out[0]->parent(), gtn);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch2 = gtn->getChild("a2");
	EXPECT_EQ(out[1]->key(), "a2");
	EXPECT_EQ(out[1]->key(), ch2->key());
	EXPECT_EQ(out[1]->data(), 3);
	EXPECT_EQ(out[1]->data(), ch2->data());
	EXPECT_EQ(out[1]->path(), "a\\a2");
	EXPECT_EQ(out[1]->parent(), gtn);

	std::shared_ptr<ds::GeneralTreeNode<int>> ch3 = gtn->getChild("b1");
	EXPECT_EQ(out[2]->key(), "b1");
	EXPECT_EQ(out[2]->key(), ch3->key());
	EXPECT_EQ(out[2]->data(), 2);
	EXPECT_EQ(out[2]->data(), ch3->data());
	EXPECT_EQ(out[2]->path(), "a\\b1");
	EXPECT_EQ(out[2]->parent(), gtn);
}
