#include <iostream>
#include <string>

#include "comparator.hpp"
#include "testing_base.h"

class TestComparator : public TestingBase {
public:

	TestComparator() : TestingBase() {}
};

template<typename T>
class CustomComparator : public ds::Comparator<T> {
public:

	int compare(const T o1, const T o2) const override {
		if (o1 == o2) {
			return 100;
		} else if (o1 > o2) {
			return 101;
		}

		return 99;
	}
};

TEST_F(TestComparator, ComparatorCreate) {
	ds::Comparator<int> comparator;

	EXPECT_EQ(comparator.compare(1, 2), -1);
	EXPECT_EQ(comparator.compare(2, 1), 1);
	EXPECT_EQ(comparator.compare(1, 1), 0);
}

TEST_F(TestComparator, ComparatorCustomStruct) {
	CustomComparator<int> comparator;

	EXPECT_EQ(comparator.compare(1, 2), 99);
	EXPECT_EQ(comparator.compare(2, 1), 101);
	EXPECT_EQ(comparator.compare(1, 1), 100);
}

TEST_F(TestComparator, ComparatorOperatorFunction) {
	CustomComparator<int> comparator;

	EXPECT_EQ(comparator(1, 2), 99);
	EXPECT_EQ(comparator(2, 1), 101);
	EXPECT_EQ(comparator(1, 1), 100);
}
