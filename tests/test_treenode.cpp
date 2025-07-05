#include <testing_base.h>

#include <TreeNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class TestTreeNode : public TestingBase {
public:

	TestTreeNode() : TestingBase() {}
};

TEST_F(TestTreeNode, Create) {
	ds::TreeNode<int> node(42);

	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.left(), nullptr);
	EXPECT_EQ(node.right(), nullptr);
	EXPECT_EQ(node.parent().use_count(), 0);
	std::cout << "TreeNode = " << node << std::endl;
};

TEST_F(TestTreeNode, Builder) {
	std::shared_ptr<ds::TreeNode<int>> node;
	ds::TreeNodeBuilder<int> builder;
	std::vector<int> children = {1, 2, 3, 4, 5};

	builder.withData(42).withChildren(children);
	node = builder.build();

	EXPECT_EQ(node->getData(), 42);
	EXPECT_TRUE(node->isRed());
	EXPECT_FALSE(node->isBlack());

	node = builder.withData(24).asBlack().build();

	EXPECT_EQ(node->getData(), 24);
	EXPECT_FALSE(node->isRed());
	EXPECT_TRUE(node->isBlack());
}
