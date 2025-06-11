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

TEST_F(TestNode, NodeClear) {
	ds::Node<int> node;

	ds::NodeBuilder<int> builder;
	node = builder.withData(1)
                  .withParentId("xyz")
                  .withRight(std::make_shared<ds::Node<int>>(2))
                  .withLeft(std::make_shared<ds::Node<int>>(3))
                  .build();

    std::string id1, id2;

    id1 = node.getId();
    EXPECT_EQ(node.getData(), 1);
    EXPECT_EQ(**node.getRight(), 2);
    EXPECT_EQ(**node.getLeft(), 3);
    EXPECT_EQ(node.getParentId(), "xyz");

    node.clear();

    id2 = node.getId();
    EXPECT_EQ(node.getData(), 1);
    EXPECT_EQ(node.getRight(), nullptr);
    EXPECT_EQ(node.getLeft(), nullptr);
    EXPECT_EQ(node.getParentId(), "");

    EXPECT_NE(id1, id2);
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
