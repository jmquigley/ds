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
	EXPECT_EQ(stack.getLength(), 0);

	stack.push(10);
	EXPECT_EQ(stack.getLength(), 1);
	EXPECT_EQ(stack.top(), 10);

	stack.push(20);
	EXPECT_EQ(stack.getLength(), 2);
	EXPECT_EQ(stack.top(), 20);

	data = stack.pop();
	EXPECT_EQ(data, 20);
	EXPECT_EQ(stack.getLength(), 1);
	EXPECT_EQ(stack.top(), 10);

	data = stack.pop();
	EXPECT_EQ(data, 10);
	EXPECT_EQ(stack.getLength(), 0);
};

TEST_F(TestStack, StackClear) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.getLength(), 0);
	stack.push(10);
	stack.push(20);
	EXPECT_EQ(stack.getLength(), 2);
	stack.clear();
	EXPECT_EQ(stack.getLength(), 0);
}

TEST_F(TestStack, StackErrors) {
	ds::Stack<int> stack;

	EXPECT_EQ(stack.getLength(), 0);
	EXPECT_THROW(stack.top(), std::runtime_error) << "Can't get top from empty stack";
	EXPECT_THROW(stack.peek(), std::runtime_error) << "Can't peek from empty stack";
	EXPECT_THROW(stack.pop(), std::runtime_error) << "Can't pop from empty stack";
};

TEST_F(TestStack, StackToString) {
	ds::Stack<int> stack;
	std::string s;

	EXPECT_EQ(stack.getLength(), 0);

	stack.push(10);
	EXPECT_EQ(stack.getLength(), 1);
	EXPECT_EQ(stack.top(), 10);

	stack.push(20);
	EXPECT_EQ(stack.getLength(), 2);
	EXPECT_EQ(stack.top(), 20);

	EXPECT_EQ(stack.str(), "[{\"data\":20},{\"data\":10}]");
}
