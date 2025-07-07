#include <testing_base.h>

#include <Deque.hpp>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class TestDeque : public TestingBase {
public:

	TestDeque() : TestingBase() {}
};

TEST_F(TestDeque, CreateQueue) {
	ds::Deque<int> q;

	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.getMaxSize(), std::numeric_limits<std::size_t>::max());

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

TEST_F(TestDeque, ConstructorWithMaxSize) {
	ds::Deque<int> q(123);

	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.getMaxSize(), 123);
}

TEST_F(TestDeque, ConstructorInitializer) {
	ds::Deque<int> q = {1, 2, 3, 4};

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.getMaxSize(), std::numeric_limits<std::size_t>::max());

	std::vector<int> a = q.drain();

	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);
	EXPECT_EQ(a[3], 4);
}

TEST_F(TestDeque, ConstructorInitializerWithParams) {
	ds::Deque<int> q(123, {1, 2, 3, 4});

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.getMaxSize(), 123);

	std::vector<int> a = q.drain();

	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);
	EXPECT_EQ(a[3], 4);
}

TEST_F(TestDeque, CheckOverlowInitializer) {
	ds::Deque<int> q(4, {1, 2, 3, 4, 5});

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.getMaxSize(), 4);

	std::vector<int> a = q.array();

	EXPECT_EQ(a[0], 2);
	EXPECT_EQ(a[1], 3);
	EXPECT_EQ(a[2], 4);
	EXPECT_EQ(a[3], 5);
}

TEST_F(TestDeque, ClearDeque) {
	ds::Deque<int> q = {1, 2, 3, 4};

	EXPECT_EQ(q.size(), 4);

	q.clear();

	EXPECT_EQ(q.size(), 0);
}

TEST_F(TestDeque, OperatorEquality) {
	ds::Deque<int> q1 = {1, 2, 3, 4};
	ds::Deque<int> q2 = {4, 3, 2, 1};

	EXPECT_FALSE(q1 == q2);
	EXPECT_TRUE(q1 != q2);
}

TEST_F(TestDeque, OperatorAddElements) {
	ds::Deque<int> q(4);

	q += 1;
	q += 2;
	q += 3;
	q += 4;

	std::vector<int> a = q.array();

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);
	EXPECT_EQ(a[3], 4);

	q += 5;

	a = q.array();

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(a[0], 2);
	EXPECT_EQ(a[1], 3);
	EXPECT_EQ(a[2], 4);
	EXPECT_EQ(a[3], 5);
}

TEST_F(TestDeque, CheckOverflowWithPush) {
	ds::Deque<int> q(4, {2, 3});

	EXPECT_EQ(q.size(), 2);
	EXPECT_EQ(q.getMaxSize(), 4);

	q.pushFront(1);
	q.pushBack(4);

	std::vector<int> a = q.array();

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);
	EXPECT_EQ(a[3], 4);

	q.pushBack(5);
	a = q.array();

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(a[0], 2);
	EXPECT_EQ(a[1], 3);
	EXPECT_EQ(a[2], 4);
	EXPECT_EQ(a[3], 5);

	q.pushFront(6);
	a = q.array();

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(a[0], 6);
	EXPECT_EQ(a[1], 3);
	EXPECT_EQ(a[2], 4);
	EXPECT_EQ(a[3], 5);
}

TEST_F(TestDeque, PopValuesFrontAndBack) {
	ds::Deque<int> q(4, {1, 2, 3, 4});

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.getMaxSize(), 4);

	std::vector<int> a = q.array();

	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);
	EXPECT_EQ(a[3], 4);

	int data = q.popFront();

	EXPECT_EQ(data, 1);
	EXPECT_EQ(q.size(), 3);

	a = q.array();

	EXPECT_EQ(a[0], 2);
	EXPECT_EQ(a[1], 3);
	EXPECT_EQ(a[2], 4);

	data = q.popBack();

	EXPECT_EQ(data, 4);
	EXPECT_EQ(q.size(), 2);

	a = q.array();

	EXPECT_EQ(a[0], 2);
	EXPECT_EQ(a[1], 3);
}

TEST_F(TestDeque, Contains) {
	ds::Queue<int> q = {1, 2, 3, 4, 5};

	EXPECT_EQ(q.size(), 5);
	EXPECT_TRUE(q.contains(4));
	EXPECT_FALSE(q.contains(7));
}
