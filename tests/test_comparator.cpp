#include <testing_base.h>

#include <ds/Comparator.hpp>
#include <ds/property.hpp>
#include <iostream>
#include <string>

class TestComparator : public TestingBase {
public:

	TestComparator() : TestingBase() {}
};

template<typename T>
class ComplexTestType {
	PROPERTY(data, Data, T);
	PROPERTY(value, Value, size_t);

public:

	ComplexTestType(T data, size_t value) : _data(data), _value(value) {}

	bool operator==(const ComplexTestType &other) const {
		return _value == other._value;
	}

	bool operator>(const ComplexTestType &other) const {
		return _value > other._value;
	}

	bool operator<(const ComplexTestType &other) const {
		return _value < other._value;
	}
};

template<typename T>
class CustomComparator : public ds::Comparator<T> {
public:

	virtual int compare(const T &o1, const T &o2) override {
		if (o1 == o2) {
			return 100;
		} else if (o1 > o2) {
			return 101;
		}

		return 99;
	}
};

TEST_F(TestComparator, DefaultComparator) {
	ds::Comparator<int> comparator;

	EXPECT_EQ(comparator.compare(1, 2), -1);
	EXPECT_EQ(comparator.compare(1, 1), 0);
	EXPECT_EQ(comparator.compare(2, 1), 1);
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

TEST_F(TestComparator, ComplexComparator) {
	ds::Comparator<ComplexTestType<int>> comparator;

	ComplexTestType c1(100, 1);
	ComplexTestType c2(200, 2);
	ComplexTestType c3(300, 1);

	EXPECT_EQ(comparator(c1, c2), -1);
	EXPECT_EQ(comparator(c1, c3), 0);
	EXPECT_EQ(comparator(c2, c1), 1);
}
