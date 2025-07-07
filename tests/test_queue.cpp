#include <testing_base.h>

#include <Queue.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

class TestQueue : public TestingBase {
public:

	TestQueue() : TestingBase() {}
};

TEST_F(TestQueue, CreateQueue) {
	ds::Queue<int> q;

	EXPECT_EQ(q.size(), 0);

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	EXPECT_EQ(q.size(), 5);
	EXPECT_EQ(q.first(), 1);
	EXPECT_EQ(q.last(), 5);

	EXPECT_EQ(q.dequeue(), 1);
	EXPECT_EQ(q.size(), 4);

	EXPECT_EQ(q.dequeue(), 2);
	EXPECT_EQ(q.size(), 3);

	EXPECT_EQ(q.dequeue(), 3);
	EXPECT_EQ(q.size(), 2);

	EXPECT_EQ(q.dequeue(), 4);
	EXPECT_EQ(q.size(), 1);

	EXPECT_EQ(q.dequeue(), 5);
	EXPECT_EQ(q.size(), 0);

	EXPECT_THROW(q.dequeue(), std::out_of_range);
}

TEST_F(TestQueue, OperatorAddElements) {
	ds::Queue<int> q;

	q += 1;
	q += 2;
	q += 3;
	q += 4;
	q += 5;

	EXPECT_EQ(q.size(), 5);
	EXPECT_EQ(q.first(), 1);
	EXPECT_EQ(q.last(), 5);
}

TEST_F(TestQueue, DequeueFromEmpty) {
	ds::Queue<int> q;

	EXPECT_EQ(q.size(), 0);
	EXPECT_THROW(q.dequeue(), std::out_of_range);
}

TEST_F(TestQueue, DrainQueue) {
	ds::Queue<int> q = {1, 2, 3, 4};

	EXPECT_EQ(q.size(), 4);

	std::vector<int> a = q.drain();

	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(a.size(), 4);

	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);
	EXPECT_EQ(a[3], 4);
}

TEST_F(TestQueue, DrainEmptyQueue) {
	ds::Queue<int> q;

	EXPECT_EQ(q.size(), 0);

	std::vector<int> a = q.drain();

	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(a.size(), 0);
}

TEST_F(TestQueue, QueueEject) {
	ds::Queue<int> q = {1, 2, 3, 4};

	EXPECT_EQ(q.size(), 4);

	q.eject(2);

	EXPECT_EQ(q.size(), 3);

	EXPECT_EQ(q.dequeue(), 1);
	EXPECT_EQ(q.dequeue(), 3);
	EXPECT_EQ(q.dequeue(), 4);

	EXPECT_EQ(q.size(), 0);
}

TEST_F(TestQueue, QueueEjectBad) {
	ds::Queue<int> q;

	EXPECT_EQ(q.size(), 0);
	EXPECT_THROW(q.eject(1), std::out_of_range);

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);

	EXPECT_EQ(q.size(), 3);
	EXPECT_THROW(q.eject(999), std::range_error);
}

TEST_F(TestQueue, Contains) {
	ds::Queue<int> q = {1, 2, 3, 4, 5};

	EXPECT_EQ(q.size(), 5);
	EXPECT_TRUE(q.contains(4));
	EXPECT_FALSE(q.contains(7));
}
