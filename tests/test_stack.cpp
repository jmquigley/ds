#include <exception>
#include <fstream>
#include <string>
#include <vector>

#include "stack.hpp"
#include "testing_base.h"

class TestStack : public TestingBase {
protected:

	TestStack() : TestingBase() {}
};

TEST_F(TestStack, StackCreate) {
	int data;
	ds::Stack<int> stack;
	EXPECT_EQ(stack.size(), 0);

	stack.push(10);
	EXPECT_EQ(stack.size(), 1);
	EXPECT_EQ(stack.top(), 10);

	stack.push(20);
	EXPECT_EQ(stack.size(), 2);
	EXPECT_EQ(stack.top(), 20);

	data = stack.pop();
	EXPECT_EQ(data, 20);
	EXPECT_EQ(stack.size(), 1);
	EXPECT_EQ(stack.top(), 10);

	data = stack.pop();
	EXPECT_EQ(data, 10);
	EXPECT_EQ(stack.size(), 0);
};

TEST_F(TestStack, StackOperatorPush) {
    ds::Stack<int> stack;

	EXPECT_EQ(stack.size(), 0);

    stack += 1;
    stack += 2;
    stack += 3;
    stack += 4;
    stack += 5;

    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);

    std::vector<int> a = stack.array();
    EXPECT_EQ(a[0], 5);
    EXPECT_EQ(a[1], 4);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 2);
    EXPECT_EQ(a[4], 1);
}

TEST_F(TestStack, StackToArray) {
    ds::Stack<int> stack = {1, 2, 3, 4, 5};

    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);

    std::vector<int> a = stack.array();
    EXPECT_EQ(a.size(), 5);

    EXPECT_EQ(a[0], 5);
    EXPECT_EQ(a[1], 4);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 2);
    EXPECT_EQ(a[4], 1);
}

TEST_F(TestStack, StackCopyConstructor) {
	ds::Stack<int> s1 = {1, 2, 3, 4, 5};

	EXPECT_EQ(s1.size(), 5);
	ds::Stack<int> s2(s1);
	EXPECT_EQ(s2.size(), 5);
    EXPECT_TRUE(s1 == s2);
}

TEST_F(TestStack, StackClear) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.size(), 0);
	stack.push(10);
	stack.push(20);
	EXPECT_EQ(stack.size(), 2);
	stack.clear();
	EXPECT_EQ(stack.size(), 0);
}

TEST_F(TestStack, StackClearOperator) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.size(), 0);
	stack.push(10);
	stack.push(20);
	EXPECT_EQ(stack.size(), 2);
	~stack;
	EXPECT_EQ(stack.size(), 0);
}

TEST_F(TestStack, StackErrors) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.size(), 0);
	EXPECT_THROW(stack.top(), std::runtime_error) << "Can't get top from empty stack";
	EXPECT_THROW(stack.peek(), std::runtime_error) << "Can't peek from empty stack";
	EXPECT_THROW(stack.pop(), std::runtime_error) << "Can't pop from empty stack";
};

TEST_F(TestStack, StackToString) {
	ds::Stack<int> stack;
	std::string s;

	EXPECT_EQ(stack.size(), 0);

	stack.push(10);
	EXPECT_EQ(stack.size(), 1);
	EXPECT_EQ(stack.top(), 10);

	stack.push(20);
	EXPECT_EQ(stack.size(), 2);
	EXPECT_EQ(stack.top(), 20);

	EXPECT_EQ(stack.str(), "[{\"data\":20},{\"data\":10}]");
}

TEST_F(TestStack, StackInitializerList) {
	ds::Stack<int> stack = {2, 4, 6, 8};

	EXPECT_EQ(stack.size(), 4);
	EXPECT_EQ(stack.top(), 8);
	EXPECT_EQ(stack.pop(), 8);

	EXPECT_EQ(stack.size(), 3);
	EXPECT_EQ(stack.top(), 6);
	EXPECT_EQ(stack.pop(), 6);

	EXPECT_EQ(stack.size(), 2);
	EXPECT_EQ(stack.top(), 4);
	EXPECT_EQ(stack.pop(), 4);

	EXPECT_EQ(stack.size(), 1);
	EXPECT_EQ(stack.top(), 2);
	EXPECT_EQ(stack.pop(), 2);

	EXPECT_EQ(stack.size(), 0);
	EXPECT_THROW(stack.top(), std::runtime_error) << "Can't get top from empty stack";
	EXPECT_THROW(stack.peek(), std::runtime_error) << "Can't peek from empty stack";
	EXPECT_THROW(stack.pop(), std::runtime_error) << "Can't pop from empty stack";
}

TEST_F(TestStack, StackEqualityOperator) {
	ds::Stack<int> s1 = {1, 2, 3, 4, 5};
	ds::Stack<int> s2 = {1, 2, 3, 4, 5};
	ds::Stack<int> s3 = {5, 4, 3, 2, 1};
	ds::Stack<int> s4 = {1, 3, 5};

	EXPECT_EQ(s1.size(), 5);
	EXPECT_EQ(s2.size(), 5);

	EXPECT_TRUE(s1 == s2);
	EXPECT_FALSE(s1 == s3);
	EXPECT_FALSE(s1 == s4);
}

TEST_F(TestStack, StackInequalityOperator) {
	ds::Stack<int> s1 = {1, 2, 3, 4, 5};
	ds::Stack<int> s2 = {1, 2, 3, 4, 5};
	ds::Stack<int> s3 = {5, 4, 3, 2, 1};
	ds::Stack<int> s4 = {1, 3, 5};

	EXPECT_EQ(s1.size(), 5);
	EXPECT_EQ(s2.size(), 5);

	EXPECT_FALSE(s1 != s2);
	EXPECT_TRUE(s1 != s3);
	EXPECT_TRUE(s1 != s4);
}

TEST_F(TestStack, StackEqualityOperatorEmpty) {
	ds::Stack<int> s1;
	ds::Stack<int> s2;

	EXPECT_EQ(s1.size(), 0);
	EXPECT_EQ(s2.size(), 0);

	EXPECT_TRUE(s1 == s2);
}

TEST_F(TestStack, StackInequalityOperatorEmpty) {
	ds::Stack<int> s1;
	ds::Stack<int> s2;

	EXPECT_EQ(s1.size(), 0);
	EXPECT_EQ(s2.size(), 0);

	EXPECT_FALSE(s1 != s2);
}
