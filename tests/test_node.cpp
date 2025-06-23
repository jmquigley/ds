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
	EXPECT_EQ(node.getParent(), nullptr);
	std::cout << "Node = " << node << std::endl;
};

TEST_F(TestNode, NodeBuilder) {
	ds::Node<int> node;
	ds::NodeBuilder<int> builder;

	builder.withData(42);
	node = builder.build();

	EXPECT_EQ(node.getData(), 42);
}

TEST_F(TestNode, NodeToString) {
	ds::Node<int> node(42);

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.getLeft(), nullptr);
	EXPECT_EQ(node.getRight(), nullptr);
	EXPECT_EQ(node.getParent(), nullptr);

	EXPECT_EQ(node.str(), "{\"data\":42}");
}

TEST_F(TestNode, NodeClear) {
	ds::Node<int> node;

	ds::NodeBuilder<int> builder;
	node = builder.withData(1)
			   .withRight(std::make_shared<ds::Node<int>>(2))
			   .withLeft(std::make_shared<ds::Node<int>>(3))
			   .build();

	std::string id1, id2;

	EXPECT_EQ(node.getData(), 1);
	EXPECT_EQ(**node.getRight(), 2);
	EXPECT_EQ(**node.getLeft(), 3);

	node.clear();

	EXPECT_EQ(node.getData(), 1);
	EXPECT_EQ(node.getRight(), nullptr);
	EXPECT_EQ(node.getLeft(), nullptr);
}

TEST_F(TestNode, NodeDereference) {
	ds::Node<int> node(1);
	EXPECT_EQ(*node, 1);

	ds::NodeBuilder<int> builder;
	builder.withData(42).withRight(std::make_shared<ds::Node<int>>(24));
	node = builder.build();

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(**node.getRight(), 24);
}
