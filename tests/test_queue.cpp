#include <testing_base.h>

#include <ds/Queue.hpp>
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
	EXPECT_EQ(q.minimum(), 1);
	EXPECT_EQ(q.maximum(), 5);

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
	EXPECT_EQ(q.minimum(), 1);
	EXPECT_EQ(q.maximum(), 5);
}

TEST_F(TestQueue, CopyConstructor) {
	ds::Queue<int> q1 = {1, 2, 3, 4};

	EXPECT_EQ(q1.size(), 4);
	std::vector<int> out = q1.array();
	EXPECT_EQ(out.size(), 4);

	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);

	ds::Queue<int> q2(q1);

	EXPECT_EQ(q2.size(), 4);

	out.clear();
	out = q2.array();

	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);

	ds::Queue<int> q3 = q2;

	out.clear();
	out = q3.array();

	EXPECT_EQ(out[0], 1);
	EXPECT_EQ(out[1], 2);
	EXPECT_EQ(out[2], 3);
	EXPECT_EQ(out[3], 4);
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

TEST_F(TestQueue, ToString) {
	ds::Queue<int> q {1, 2, 3};
	std::string result =
		"[{\"data\":1,\"color\":\"red\"},{\"data\":2,\"color\":\"red\"},{"
		"\"data\":3,\"color\":"
		"\"red\"}]";

	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.str(), result);
	EXPECT_EQ(q.json(), result);
}

TEST_F(TestQueue, ToStringEmpty) {
	ds::Queue<int> q;

	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.str(), "[]");
}
