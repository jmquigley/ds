#include "test_node.h"

#include <string>

#include "node.h"

TestNode::TestNode() {
  memset(temp, 0, sizeof(temp));
  bufptr = nullptr;
};

TEST_F(TestNode, NodeCreate) {
    Node<int> node;
    EXPECT_TRUE(true);
};
