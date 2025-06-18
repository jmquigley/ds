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

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	EXPECT_EQ(q.getSize(), 5);
	EXPECT_EQ(**q.getFront(), 1);
	EXPECT_EQ(**q.getBack(), 5);

	EXPECT_EQ(q.dequeue(), 1);
	EXPECT_EQ(q.getSize(), 4);

	EXPECT_EQ(q.dequeue(), 2);
	EXPECT_EQ(q.getSize(), 3);

	EXPECT_EQ(q.dequeue(), 3);
	EXPECT_EQ(q.getSize(), 2);

	EXPECT_EQ(q.dequeue(), 4);
	EXPECT_EQ(q.getSize(), 1);

	EXPECT_EQ(q.dequeue(), 5);
	EXPECT_EQ(q.getSize(), 0);

	EXPECT_THROW(q.dequeue(), std::out_of_range);
}
