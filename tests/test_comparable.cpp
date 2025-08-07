#include <testing_base.h>

#include <ds/Comparable.hpp>
#include <ds/property.hpp>
#include <iostream>
#include <string>

class TestComparable : public TestingBase {
public:

	TestComparable() : TestingBase() {}
};

template<typename T>
class ComplexTestType : public ds::Comparable<ComplexTestType<T>> {
	PROPERTY(data, Data, T);
	PROPERTY(value, Value, size_t);

public:

	ComplexTestType(T data, size_t value) : _data(data), _value(value) {}

	virtual ~ComplexTestType() = default;

	virtual bool operator==(
		const ComplexTestType<T> &other) const noexcept override {
		return _value == other._value;
	}

	virtual bool operator!=(
		const ComplexTestType<T> &other) const noexcept override {
		return _value != other._value;
	}

	virtual bool operator>(
		const ComplexTestType<T> &other) const noexcept override {
		return _value > other._value;
	}

	virtual bool operator<(
		const ComplexTestType<T> &other) const noexcept override {
		return _value < other._value;
	}

	virtual bool operator<=(
		const ComplexTestType<T> &other) const noexcept override {
		return _value <= other._value;
	}

	virtual bool operator>=(
		const ComplexTestType<T> &other) const noexcept override {
		return _value >= other._value;
	}

	virtual void print(std::ostream &os) const override {
		os << "data: " << _data << ", value: " << _value;
	}
};

TEST_F(TestComparable, EqualityComparison) {
	ComplexTestType<int> a(10, 5);
	ComplexTestType<int> b(20, 5);	 // Different data but same value
	ComplexTestType<int> c(30, 10);	 // Different value

	EXPECT_TRUE(a == b);   // Same value (5)
	EXPECT_FALSE(a == c);  // Different value (5 vs 10)
	EXPECT_FALSE(a != b);  // Not different
	EXPECT_TRUE(a != c);   // Different
}

TEST_F(TestComparable, OrderingComparison) {
	ComplexTestType<int> a(10, 5);
	ComplexTestType<int> b(20, 10);

	EXPECT_TRUE(a < b);	   // 5 < 10
	EXPECT_TRUE(a <= b);   // 5 <= 10
	EXPECT_FALSE(a > b);   // 5 > 10
	EXPECT_FALSE(a >= b);  // 5 >= 10
}

TEST_F(TestComparable, CompareMethod) {
	ComplexTestType<int> a(10, 5);
	ComplexTestType<int> b(20, 5);
	ComplexTestType<int> c(30, 10);

	EXPECT_EQ(a.compare(a, b), 0);	 // Equal values
	EXPECT_EQ(a.compare(a, c), -1);	 // a < c
	EXPECT_EQ(a.compare(c, a), 1);	 // c > a
}
