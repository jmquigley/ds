#include <testing_base.h>

#include <PriorityQueue.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

class TestPriorityQueue : public TestingBase {
public:

	TestPriorityQueue() : TestingBase() {}
};

TEST_F(TestPriorityQueue, PriorityClass) {
	ds::Priority<std::string> pri1("p1", 100, 1);

	EXPECT_EQ(pri1.data(), "p1");
	EXPECT_EQ(pri1.value(), 100);
	EXPECT_EQ(pri1.offset(), 1);
	EXPECT_EQ(pri1.key(), "000000100:000000001");
	EXPECT_EQ(pri1.str(), "\"data\":\"p1\", \"key\":\"000000100:000000001\"");

	ds::Priority<std::string> pri2("p2", 200, 199);

	EXPECT_EQ(pri2.data(), "p2");
	EXPECT_EQ(pri2.value(), 200);
	EXPECT_EQ(pri2.offset(), 199);
	EXPECT_EQ(pri2.key(), "000000200:000000199");
	EXPECT_EQ(pri2.str(), "\"data\":\"p2\", \"key\":\"000000200:000000199\"");
}

TEST_F(TestPriorityQueue, CreatePriorityQueue) {
	ds::PriorityQueue<std::string> pq;

	EXPECT_EQ(pq.size(), 0);
	EXPECT_TRUE(pq.empty());

	ds::Priority<std::string> p1 = pq.enqueue("a", 100);
	ds::Priority<std::string> p2 = pq.enqueue("c", 100);
	ds::Priority<std::string> p3 = pq.enqueue("b", 100);
	ds::Priority<std::string> p4 = pq.enqueue("d", 100);

	EXPECT_EQ(pq.size(), 4);
	EXPECT_FALSE(pq.empty());

	ds::Priority<std::string> ret = pq.minimum();

	EXPECT_EQ(ret.data(), "a");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 1);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "a");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 1);
	EXPECT_EQ(pq.size(), 3);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "c");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 2);
	EXPECT_EQ(pq.size(), 2);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "b");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 3);
	EXPECT_EQ(pq.size(), 1);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "d");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 4);
	EXPECT_EQ(pq.size(), 0);
}

TEST_F(TestPriorityQueue, Initializer) {
	ds::PriorityQueue<std::string> pq {
		{"a", 100, 1}, {"c", 100, 2}, {"b", 100, 3}, {"d", 100, 4}};

	EXPECT_EQ(pq.size(), 4);
	EXPECT_FALSE(pq.empty());

	ds::Priority<std::string> ret = pq.minimum();

	EXPECT_EQ(ret.data(), "a");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 1);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "a");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 1);
	EXPECT_EQ(pq.size(), 3);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "c");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 2);
	EXPECT_EQ(pq.size(), 2);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "b");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 3);
	EXPECT_EQ(pq.size(), 1);

	ret = pq.dequeue();

	EXPECT_EQ(ret.data(), "d");
	EXPECT_EQ(ret.value(), 100);
	EXPECT_EQ(ret.offset(), 4);
	EXPECT_EQ(pq.size(), 0);
}

// TODO: test PriorityQueue copy constructor and assignment
// TODO: test PriorityQueue removal and clearing
// TODO: test PriorityQueue drain
// TODO: test PriorityQueue toString
// TODO: test PriorityQueue comparison operators
// TODO: test PriorityQueue enqueue operators
