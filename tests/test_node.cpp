#include <testing_base.h>

#include <Node.hpp>
#include <iostream>
#include <string>

class TestNode : public TestingBase {
public:

	TestNode() : TestingBase() {}
};

TEST_F(TestNode, Create) {
	ds::Node<int> node(42);

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.left(), nullptr);
	EXPECT_EQ(node.right(), nullptr);
	std::cout << "Node = " << node << std::endl;
};

TEST_F(TestNode, Builder) {
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

TEST_F(TestNode, ToString) {
	ds::Node<int> node(42);
	std::string result = "{\"data\":42,\"color\":\"red\"}";

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.getLeft(), nullptr);
	EXPECT_EQ(node.getRight(), nullptr);

	EXPECT_EQ(node.str(), result);
}

TEST_F(TestNode, Clear) {
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

TEST_F(TestNode, DeepCopy) {
	ds::Node<int> node1(42);

	EXPECT_EQ(node1.data(), 42);
	EXPECT_TRUE(node1.isRed());

	ds::Node<int> node2 = node1.deepcopy();

	EXPECT_EQ(node2.data(), 42);
	EXPECT_TRUE(node2.isRed());
	EXPECT_TRUE(&node1 != &node2);
}

TEST_F(TestNode, Dereference) {
	ds::Node<int> node(1);
	EXPECT_EQ(*node, 1);

	std::shared_ptr<ds::Node<int>> node2;
	ds::NodeBuilder<int> builder;
	builder.withData(42).withRight(std::make_shared<ds::Node<int>>(24));
	node2 = builder.build();

	EXPECT_EQ(node2->getData(), 42);
	EXPECT_EQ(**node2->getRight(), 24);
}

TEST_F(TestNode, Color) {
	ds::Node<int> node(42);
	std::string resultRed = "{\"data\":42,\"color\":\"red\"}";
	std::string resultBlack = "{\"data\":42,\"color\":\"black\"}";

	// Default should be red
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());

	// Test setting to black
	node.setBlack();
	EXPECT_TRUE(node.isBlack());
	EXPECT_FALSE(node.isRed());
	EXPECT_EQ(node.str(), resultBlack);

	// Test setting back to red
	node.setRed();
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());
	EXPECT_EQ(node.str(), resultRed);
}

TEST_F(TestNode, ColorWithBuilder) {
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
