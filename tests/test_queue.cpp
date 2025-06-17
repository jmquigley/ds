#include <iostream>
#include <string>

#include "queue.hpp"
#include "testing_base.h"

class TestQueue : public TestingBase {
public:

	TestQueue() : TestingBase() {}
};

TEST_F(TestQueue, CreateQueue) {
    EXPECT_TRUE(true);
}
