#include <testing_base.h>

#include <ds/Node.hpp>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

class TestNode : public TestingBase {
protected:

	std::shared_ptr<ds::Node<int>> left;
	std::shared_ptr<ds::Node<int>> right;

public:

	TestNode() = default;

	auto SetUp() -> void override {
		left = std::make_shared<ds::Node<int>>(1);
		right = std::make_shared<ds::Node<int>>(2);
	}

	void TearDown() override {
		left.reset();
		right.reset();
	}
};

TEST_F(TestNode, Create) {
	ds::Node<int> node;

	EXPECT_EQ(node.data(), 0);
	EXPECT_EQ(node.left(), nullptr);
	EXPECT_EQ(node.right(), nullptr);
	EXPECT_EQ(node.flags(), 0);
};

TEST_F(TestNode, ParameterizedConstructor) {
	ds::Node<int> node(42);

	EXPECT_EQ(node.data(), 42);
	EXPECT_EQ(node.left(), nullptr);
	EXPECT_EQ(node.right(), nullptr);

	int &x = node.data();
	EXPECT_EQ(x, 42);
	x = 24;
	EXPECT_EQ(x, 24);
	EXPECT_EQ(node.data(), 24);
}

TEST_F(TestNode, CopyConstructor) {
	ds::Node<int> node(42);
	EXPECT_EQ(node.getData(), 42);
	EXPECT_EQ(node.left(), nullptr);
	EXPECT_EQ(node.right(), nullptr);

	ds::Node<int> node2(node);
	EXPECT_EQ(node2.getData(), 42);
	EXPECT_EQ(node2.left(), nullptr);
	EXPECT_EQ(node2.right(), nullptr);

	ds::Node<int> node3(left, right, (ds::ByteFlag)99, 42);
	EXPECT_EQ(node3.getData(), 42);
	EXPECT_EQ(node3.left(), left);
	EXPECT_EQ(node3.right(), right);
	EXPECT_EQ(node3.left()->data(), 1);
	EXPECT_EQ(node3.right()->data(), 2);

	ds::Node<int> node4(node3);
	EXPECT_EQ(node4.getData(), 42);
	EXPECT_EQ(node4.left(), left);
	EXPECT_EQ(node4.right(), right);
	EXPECT_EQ(node4.left()->data(), 1);
	EXPECT_EQ(node4.right()->data(), 2);
}

TEST_F(TestNode, MoveConstructor) {
	ds::Node<int> node3(left, right, (ds::ByteFlag)99, 42);

	EXPECT_EQ(node3.data(), 42);
	EXPECT_EQ(node3.flags(), (ds::ByteFlag)99);
	EXPECT_EQ(node3.left(), left);
	EXPECT_EQ(node3.right(), right);
	EXPECT_EQ(node3.left()->data(), 1);
	EXPECT_EQ(node3.right()->data(), 2);

	ds::Node<int> node4(std::move(node3));

	EXPECT_EQ(node4.data(), 42);
	EXPECT_EQ(node4.flags(), (ds::ByteFlag)99);
	EXPECT_EQ(node4.left(), left);
	EXPECT_EQ(node4.right(), right);
	EXPECT_EQ(node4.left()->data(), 1);
	EXPECT_EQ(node4.right()->data(), 2);

	EXPECT_EQ(node3.left(), nullptr);
	EXPECT_EQ(node3.right(), nullptr);
}

TEST_F(TestNode, AssignmentOperators) {
	ds::Node<int> node;
	node = 42;
	EXPECT_EQ(node.data(), 42);
	EXPECT_EQ(node.flags(), 0);

	ds::Node<int> node1(123);
	node = node1;
	EXPECT_EQ(node.data(), 123);
	EXPECT_EQ(node.flags(), 0);

	ds::Node<int> node2(left, right, (ds::ByteFlag)99, 24);

	node = node2;

	EXPECT_EQ(node.data(), 24);
	EXPECT_EQ(node.flags(), (ds::ByteFlag)99);
	EXPECT_EQ(node.left(), left);
	EXPECT_EQ(node.right(), right);
	EXPECT_EQ(node.left()->data(), 1);
	EXPECT_EQ(node.right()->data(), 2);
}

TEST_F(TestNode, CallOperator) {
	ds::Node<int> node(left, right, 42);

	EXPECT_EQ(node.data(), 42);
	EXPECT_EQ(node.flags(), 0);
	EXPECT_EQ(node.left(), left);
	EXPECT_EQ(node.right(), right);
	EXPECT_EQ(node.left()->data(), 1);
	EXPECT_EQ(node.right()->data(), 2);

	ds::Node<int> node2;
	EXPECT_EQ(node2.data(), 0);
	EXPECT_EQ(node2.flags(), 0);
	EXPECT_EQ(node2.left(), nullptr);
	EXPECT_EQ(node2.right(), nullptr);

	node2(node);

	EXPECT_EQ(node2.data(), 42);
	EXPECT_EQ(node2.flags(), 0);
	EXPECT_EQ(node2.left(), left);
	EXPECT_EQ(node2.right(), right);
	EXPECT_EQ(node2.left()->data(), 1);
	EXPECT_EQ(node2.right()->data(), 2);
}

TEST_F(TestNode, Compare) {
	ds::Node<int> n1(42);
	ds::Node<int> n2(24);

	EXPECT_TRUE(n1 == n1);
	EXPECT_FALSE(n1 == n2);

	EXPECT_TRUE(n1 != n2);
	EXPECT_FALSE(n1 != n1);
}

TEST_F(TestNode, Logical) {
	ds::Node<int> n1(42);
	ds::Node<int> n2(24);

	// Less Than
	EXPECT_TRUE(n2 < n1);
	EXPECT_FALSE(n1 < n2);

	// Greater Than
	EXPECT_TRUE(n1 > n2);
	EXPECT_FALSE(n2 > n1);

	// Less than or equal
	EXPECT_TRUE(n2 <= n1);
	EXPECT_FALSE(n1 <= n2);
	EXPECT_TRUE(n2 <= n2);

	// Greater than or equal
	EXPECT_TRUE(n1 >= n2);
	EXPECT_FALSE(n2 >= n1);
	EXPECT_TRUE(n2 >= n2);
}

TEST_F(TestNode, ToString) {
	ds::Node<int> node(42);

	std::string result = R"({"data":42,"color":"red"})";

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

	EXPECT_EQ(node->getData(), 1);
	EXPECT_EQ(**node->getRight(), 2);
	EXPECT_EQ(**node->getLeft(), 3);

	node->clear();

	EXPECT_EQ(node->getRight(), nullptr);
	EXPECT_EQ(node->getLeft(), nullptr);
}

TEST_F(TestNode, DeepCopy) {
	ds::Node<int> node1(42);

	EXPECT_EQ(node1.data(), 42);
	EXPECT_TRUE(node1.isRed());

	std::shared_ptr<ds::Node<int>> node2 = node1.deepcopy();

	EXPECT_EQ(node2->data(), 42);
	EXPECT_TRUE(node2->isRed());
	EXPECT_TRUE(&node1 != node2.get());
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
	std::string resultRed = R"({"data":42,"color":"red"})";
	std::string resultBlack = R"({"data":42,"color":"black"})";

	// Default should be red
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());

	// Test setting to black
	node.setBlack();
	EXPECT_TRUE(node.isBlack());
	EXPECT_FALSE(node.isRed());
	EXPECT_EQ(node.str(), resultBlack);
	EXPECT_EQ(node.getColor(), ds::NodeColor::Black);

	// Test setting back to red
	node.setRed();
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());
	EXPECT_EQ(node.str(), resultRed);
	EXPECT_EQ(node.getColor(), ds::NodeColor::Red);

	// Test setting back to black
	node.setColor(ds::NodeColor::Black);
	EXPECT_TRUE(node.isBlack());
	EXPECT_FALSE(node.isRed());
	EXPECT_EQ(node.getColor(), ds::NodeColor::Black);

	// Test setting back to red
	node.setColor(ds::NodeColor::Red);
	EXPECT_TRUE(node.isRed());
	EXPECT_FALSE(node.isBlack());
	EXPECT_EQ(node.getColor(), ds::NodeColor::Red);
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

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
