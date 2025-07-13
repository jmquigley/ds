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
	auto pgtn = std::make_shared<ds::GeneralTreeNode<int>>("a", 42);

	EXPECT_EQ(pgtn->data(), 42);
	EXPECT_EQ(pgtn->parent(), nullptr);

	pgtn->addChild("a1", 1);
	pgtn->addChild("b1", 2);
	pgtn->addChild("a2", 3);

	EXPECT_EQ(pgtn->totalChildren(), 3);

	std::vector<std::shared_ptr<ds::GeneralTreeNode<int>>> out =
		pgtn->getChildren();

	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0]->data(), 1);

	EXPECT_EQ(out[1]->key(), "a2");
	EXPECT_EQ(out[1]->data(), 3);

	EXPECT_EQ(out[2]->key(), "b1");
	EXPECT_EQ(out[2]->data(), 2);

	pgtn->removeChild("a2");

	EXPECT_EQ(pgtn->totalChildren(), 2);

	out = pgtn->getChildren();

	EXPECT_EQ(out[0]->key(), "a1");
	EXPECT_EQ(out[0]->data(), 1);

	EXPECT_EQ(out[1]->key(), "b1");
	EXPECT_EQ(out[1]->data(), 2);

	pgtn.reset();
};
