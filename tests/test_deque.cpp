#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "deque.hpp"
#include "testing_base.h"

class TestDeque : public TestingBase {
public:

	TestDeque() : TestingBase() {}
};

TEST_F(TestDeque, CreateQueue) {
	ds::Deque<int> q;

	EXPECT_EQ(q.size(), 0);

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	EXPECT_EQ(q.size(), 5);
	EXPECT_EQ(q.front(), 1);
	EXPECT_EQ(q.back(), 5);

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
