#include <exception>
#include <iostream>
#include <string>
#include <vector>

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
	q.push(4);
	q.push(5);

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

TEST_F(TestQueue, DequeueFromEmpty) {
    ds::Queue<int> q;

    EXPECT_EQ(q.getSize(), 0);
    EXPECT_THROW(q.dequeue(), std::out_of_range);
}

TEST_F(TestQueue, DrainQueue) {
    ds::Queue<int> q = {1, 2, 3, 4};

    EXPECT_EQ(q.getSize(), 4);

    std::vector<int> a = q.drain();

    EXPECT_EQ(q.getSize(), 0);
    EXPECT_EQ(a.size(), 4);
}

TEST_F(TestQueue, DrainEmptyQueue) {
    ds::Queue<int> q;

    EXPECT_EQ(q.getSize(), 0);

    std::vector<int> a = q.drain();

    EXPECT_EQ(q.getSize(), 0);
    EXPECT_EQ(a.size(), 0);
}

TEST_F(TestQueue, QueueEject) {
    ds::Queue<int> q = {1, 2, 3, 4};

    EXPECT_EQ(q.getSize(), 4);

    q.eject(2);

    EXPECT_EQ(q.getSize(), 3);

	EXPECT_EQ(q.dequeue(), 1);
	EXPECT_EQ(q.dequeue(), 3);
	EXPECT_EQ(q.dequeue(), 4);

    EXPECT_EQ(q.getSize(), 0);
}

TEST_F(TestQueue, QueueEjectBad) {
    ds::Queue<int> q;

    EXPECT_EQ(q.getSize(), 0);
    EXPECT_THROW(q.eject(1), std::out_of_range);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    EXPECT_EQ(q.getSize(), 3);
    EXPECT_THROW(q.eject(999), std::range_error);
}
