#include <iostream>
#include <string>

#include "queue.hpp"
#include "testing_base.h"

class TestQueue : public TestingBase {
public:

	TestQueue() : TestingBase() {}
};

TEST_F(TestQueue, CreateQueue) {
    ds::Queue<int> q;

    EXPECT_EQ(q.getSize(), 0);
    EXPECT_TRUE(true);
}
