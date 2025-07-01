#include <iostream>
#include <string>

#include "node.hpp"
#include "testing_base.h"

class TestNode : public TestingBase {
public:

	TestNode() : TestingBase() {}
};

TEST_F(TestNode, NodeCreate) {
	ds::Node<int> node(42);

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.getLeft(), nullptr);
	EXPECT_EQ(node.getRight(), nullptr);
	EXPECT_EQ(node.getParent().use_count(), 0);
	std::cout << "Node = " << node << std::endl;
};

TEST_F(TestNode, NodeBuilder) {
	std::shared_ptr<ds::Node<int>> node;
	ds::NodeBuilder<int> builder;

	builder.withData(42);
	node = builder.build();

	EXPECT_EQ(node->getData(), 42);
	EXPECT_TRUE(node->isRed());
	EXPECT_FALSE(node->isBlack());

	node = builder.withData(24).asBlack().build();

	EXPECT_EQ(node->getData(), 24);
	EXPECT_FALSE(node->isRed());
	EXPECT_TRUE(node->isBlack());
}

TEST_F(TestNode, NodeToString) {
	ds::Node<int> node(42);

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.getLeft(), nullptr);
	EXPECT_EQ(node.getRight(), nullptr);
	EXPECT_EQ(node.getParent().use_count(), 0);

	EXPECT_EQ(node.str(), "{\"data\":42,\"color\":\"red\"\"parent\":\"invalid\"}");
}

TEST_F(TestNode, NodeClear) {
	std::shared_ptr<ds::Node<int>> node;
	ds::NodeBuilder<int> builder;

	node = builder.withData(1)
			   .withRight(std::make_shared<ds::Node<int>>(2))
			   .withLeft(std::make_shared<ds::Node<int>>(3))
			   .build();

	std::string id1, id2;

	EXPECT_EQ(node->getData(), 1);
	EXPECT_EQ(**node->getRight(), 2);
	EXPECT_EQ(**node->getLeft(), 3);

	node->clear();

	EXPECT_EQ(node->getData(), 1);
	EXPECT_EQ(node->getRight(), nullptr);
	EXPECT_EQ(node->getLeft(), nullptr);
}

TEST_F(TestNode, NodeDereference) {
	ds::Node<int> node(1);
	EXPECT_EQ(*node, 1);

	std::shared_ptr<ds::Node<int>> node2;
	ds::NodeBuilder<int> builder;
	builder.withData(42).withRight(std::make_shared<ds::Node<int>>(24));
	node2 = builder.build();

	EXPECT_EQ(node2->getData(), 42);
	EXPECT_EQ(**node2->getRight(), 24);
}

TEST_F(TestNode, NodeColor) {
	ds::Node<int> node(42);

	// Default should be red
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());

	// Test setting to black
	node.setBlack();
	EXPECT_TRUE(node.isBlack());
	EXPECT_FALSE(node.isRed());

	// Test setting back to red
	node.setRed();
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());
}

TEST_F(TestNode, NodeColorWithBuilder) {
	std::shared_ptr<ds::Node<int>> node;
	ds::NodeBuilder<int> builder;

	node = builder.withData(42).build();

	// Default should be red
	EXPECT_TRUE(node->isRed());
	EXPECT_FALSE(node->isBlack());

	// Test toggling colors
	node->setBlack();
	EXPECT_TRUE(node->isBlack());
	EXPECT_FALSE(node->isRed());

	node->setRed();
	EXPECT_TRUE(node->isRed());
	EXPECT_FALSE(node->isBlack());
}
