#include "test_stack.h"

#include <string>

#include "stack.hpp"

using namespace ds;

TestStack::TestStack() {
  memset(temp, 0, sizeof(temp));
  bufptr = nullptr;
};

TEST_F(TestStack, StackCreate) {
    Stack<int> stack;
    EXPECT_EQ(stack.getLength(), 0);
};
