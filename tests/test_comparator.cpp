#include <iostream>
#include <string>

#include "comparator.hpp"
#include "testing_base.h"

class TestComparator : public TestingBase {
public:

	TestComparator() : TestingBase() {}
};

TEST_F(TestComparator, ComparatorCreate) {
	ds::Comparator<int> comparator;

	EXPECT_EQ(comparator.compare(1, 2), -1);
	EXPECT_EQ(comparator.compare(2, 1), 1);
	EXPECT_EQ(comparator.compare(1, 1), 0);
};

template<typename T>
class CustomComparator : public ds::Comparator<T> {
public:

	int compare(T o1, T o2) override {
		if (o1 == o2) {
			return 100;
		} else if (o1 > o2) {
			return 101;
		}

		return 99;
	}
};

TEST_F(TestComparator, ComparatorCustomStruct) {
	CustomComparator<int> comparator;

	EXPECT_EQ(comparator.compare(1, 2), 99);
	EXPECT_EQ(comparator.compare(2, 1), 101);
	EXPECT_EQ(comparator.compare(1, 1), 100);
}
