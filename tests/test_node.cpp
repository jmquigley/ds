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

	std::string s;
	s = node.getParentId();
	EXPECT_EQ(s.length(), 0);

	s = node.getId();
	EXPECT_EQ(s.length(), 36);
	std::cout << "Node = " << node << std::endl;
};

TEST_F(TestNode, NodeBuilder) {
	ds::Node<int> node;
	ds::NodeBuilder<int> builder;

	builder.withData(42).withParentId("xyz");
	node = std::move(builder.build());

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.getParentId(), "xyz");
	EXPECT_EQ(node.getId().length(), 36);
}

TEST_F(TestNode, NodeToString) {
	ds::Node<int> node(42);

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.getLeft(), nullptr);
	EXPECT_EQ(node.getRight(), nullptr);
	EXPECT_EQ(node.getParent(), nullptr);

	EXPECT_EQ(node.str(), "{\"data\":42}");
}
