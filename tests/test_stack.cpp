#include <exception>
#include <fstream>
#include <string>

#include "stack.hpp"
#include "testing_base.h"

class TestStack : public TestingBase {
protected:

	TestStack() : TestingBase() {}
};

TEST_F(TestStack, StackCreate) {
	int data;
	ds::Stack<int> stack;
	EXPECT_EQ(stack.getSize(), 0);

	stack.push(10);
	EXPECT_EQ(stack.getSize(), 1);
	EXPECT_EQ(stack.top(), 10);

	stack.push(20);
	EXPECT_EQ(stack.getSize(), 2);
	EXPECT_EQ(stack.top(), 20);

	data = stack.pop();
	EXPECT_EQ(data, 20);
	EXPECT_EQ(stack.getSize(), 1);
	EXPECT_EQ(stack.top(), 10);

	data = stack.pop();
	EXPECT_EQ(data, 10);
	EXPECT_EQ(stack.getSize(), 0);
};

TEST_F(TestStack, StackClear) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.getSize(), 0);
	stack.push(10);
	stack.push(20);
	EXPECT_EQ(stack.getSize(), 2);
	stack.clear();
	EXPECT_EQ(stack.getSize(), 0);
}

TEST_F(TestStack, StackClearOperator) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.getSize(), 0);
	stack.push(10);
	stack.push(20);
	EXPECT_EQ(stack.getSize(), 2);
	~stack;
	EXPECT_EQ(stack.getSize(), 0);
}

TEST_F(TestStack, StackErrors) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.getSize(), 0);
	EXPECT_THROW(stack.top(), std::runtime_error) << "Can't get top from empty stack";
	EXPECT_THROW(stack.peek(), std::runtime_error) << "Can't peek from empty stack";
	EXPECT_THROW(stack.pop(), std::runtime_error) << "Can't pop from empty stack";
};

TEST_F(TestStack, StackToString) {
	ds::Stack<int> stack;
	std::string s;

	EXPECT_EQ(stack.getSize(), 0);

	stack.push(10);
	EXPECT_EQ(stack.getSize(), 1);
	EXPECT_EQ(stack.top(), 10);

	stack.push(20);
	EXPECT_EQ(stack.getSize(), 2);
	EXPECT_EQ(stack.top(), 20);

	EXPECT_EQ(stack.str(), "[{\"data\":20},{\"data\":10}]");
}

TEST_F(TestStack, StackInitializerList) {
    ds::Stack<int> stack = {2, 4, 6, 8};

    EXPECT_EQ(stack.getSize(), 4);
    EXPECT_EQ(stack.top(), 8);
    EXPECT_EQ(stack.pop(), 8);

    EXPECT_EQ(stack.getSize(), 3);
    EXPECT_EQ(stack.top(), 6);
    EXPECT_EQ(stack.pop(), 6);

    EXPECT_EQ(stack.getSize(), 2);
    EXPECT_EQ(stack.top(), 4);
    EXPECT_EQ(stack.pop(), 4);

    EXPECT_EQ(stack.getSize(), 1);
    EXPECT_EQ(stack.top(), 2);
    EXPECT_EQ(stack.pop(), 2);

    EXPECT_EQ(stack.getSize(), 0);
	EXPECT_THROW(stack.top(), std::runtime_error) << "Can't get top from empty stack";
	EXPECT_THROW(stack.peek(), std::runtime_error) << "Can't peek from empty stack";
	EXPECT_THROW(stack.pop(), std::runtime_error) << "Can't pop from empty stack";
}

TEST_F(TestStack, StackEqualityOperator) {
    ds::Stack<int> s1 = {1, 2, 3, 4, 5};
    ds::Stack<int> s2 = {1, 2, 3, 4, 5};
    ds::Stack<int> s3 = {5, 4, 3, 2, 1};
    ds::Stack<int> s4 = {1, 3, 5};

    EXPECT_EQ(s1.getSize(), 5);
    EXPECT_EQ(s2.getSize(), 5);

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_FALSE(s1 == s4);
}

TEST_F(TestStack, StackInequalityOperator) {
    ds::Stack<int> s1 = {1, 2, 3, 4, 5};
    ds::Stack<int> s2 = {1, 2, 3, 4, 5};
    ds::Stack<int> s3 = {5, 4, 3, 2, 1};
    ds::Stack<int> s4 = {1, 3, 5};

    EXPECT_EQ(s1.getSize(), 5);
    EXPECT_EQ(s2.getSize(), 5);

    EXPECT_FALSE(s1 != s2);
    EXPECT_TRUE(s1 != s3);
    EXPECT_TRUE(s1 != s4);
}

TEST_F(TestStack, StackEqualityOperatorEmpty) {
    ds::Stack<int> s1;
    ds::Stack<int> s2;

    EXPECT_EQ(s1.getSize(), 0);
    EXPECT_EQ(s2.getSize(), 0);

    EXPECT_TRUE(s1 == s2);
}

TEST_F(TestStack, StackInequalityOperatorEmpty) {
    ds::Stack<int> s1;
    ds::Stack<int> s2;

    EXPECT_EQ(s1.getSize(), 0);
    EXPECT_EQ(s2.getSize(), 0);

    EXPECT_FALSE(s1 != s2);
}
