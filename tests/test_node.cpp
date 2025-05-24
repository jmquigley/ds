#include "test_node.h"

#include <string>

TestNode::TestNode() {
  memset(temp, 0, sizeof(temp));
  bufptr = nullptr;
};

TEST_F(TestNode, NodeCreate) { EXPECT_TRUE(true); };
