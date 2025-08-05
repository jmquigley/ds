#include <testing_base.h>

#include <ds/List.hpp>
#include <ds/property.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class TestList : public TestingBase {
public:

	TestList() : TestingBase() {}
};

TEST_F(TestList, Create) {
	ds::List<int> list;
	EXPECT_EQ(list.size(), 0);

	list.insert(1);
	EXPECT_EQ(list.size(), 1);	// root insert

	list.insert(2);
	EXPECT_EQ(list.size(), 2);	// second insert

	list += 3;
	EXPECT_EQ(list.size(), 3);	// third insert

	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);
}

TEST_F(TestList, Constructors) {
	// Initialization list constructor
	ds::List<int> l1 {1, 2, 3, 4, 5};

	EXPECT_EQ(l1.size(), 5);
	EXPECT_EQ(l1.at(0), 1);
	EXPECT_EQ(l1.at(1), 2);
	EXPECT_EQ(l1.at(2), 3);
	EXPECT_EQ(l1.at(3), 4);
	EXPECT_EQ(l1.at(4), 5);
	EXPECT_EQ(**l1.front().lock(), 1);
	EXPECT_EQ(l1.minimum(), 1);
	EXPECT_EQ(**l1.back().lock(), 5);
	EXPECT_EQ(l1.maximum(), 5);
	EXPECT_FALSE(l1.empty());

	auto it1 = l1.begin();
	auto it2 = l1.end();

	EXPECT_EQ(*it1, 1);
	EXPECT_EQ(*it1.next(), 2);
	EXPECT_EQ(*it1.next(), 3);
	EXPECT_EQ(*it1.next(), 4);
	EXPECT_EQ(*it1.next(), 5);
	EXPECT_EQ(*it1.next(), 0);

	// Copy constructor
	ds::List<int> l2(l1);

	EXPECT_TRUE(l1.root() != l2.root());
	EXPECT_EQ(l2.size(), 5);
	EXPECT_EQ(l2.at(0), 1);
	EXPECT_EQ(l2.at(1), 2);
	EXPECT_EQ(l2.at(2), 3);
	EXPECT_EQ(l2.at(3), 4);
	EXPECT_EQ(l2.at(4), 5);
	EXPECT_EQ(**l2.front().lock(), 1);
	EXPECT_EQ(l2.minimum(), 1);
	EXPECT_EQ(**l2.back().lock(), 5);
	EXPECT_EQ(l2.maximum(), 5);
	EXPECT_FALSE(l2.empty());

	it1 = l1.begin();
	it2 = l2.begin();

	EXPECT_TRUE(it1.get() != it2.get());

	it1.next();
	it2.next();

	EXPECT_TRUE(it1.get() != it2.get());

	// Assignment/copy constructor
	ds::List<int> l3 = l2;
	EXPECT_EQ(l3.size(), 5);

	EXPECT_EQ(l3.at(0), 1);
	EXPECT_EQ(l3.at(1), 2);
	EXPECT_EQ(l3.at(2), 3);
	EXPECT_EQ(l3.at(3), 4);
	EXPECT_EQ(l3.at(4), 5);

	l3.clear();
	l3.insert(1);
	l3.insert(2);
	l3.insert(3);

	EXPECT_EQ(l3.size(), 3);
	EXPECT_EQ(l3.at(0), 1);
	EXPECT_EQ(l3.at(1), 2);
	EXPECT_EQ(l3.at(2), 3);

	// Move constructor
	ds::List<int> l4(std::move(l3));

	EXPECT_EQ(l4.size(), 3);
	EXPECT_EQ(l4.at(0), 1);
	EXPECT_EQ(l4.at(1), 2);
	EXPECT_EQ(l4.at(2), 3);

	EXPECT_EQ(l3.size(), 0);
	EXPECT_EQ(l3.root(), nullptr);
	EXPECT_EQ(l3.front().use_count(), 0);
	EXPECT_EQ(l3.back().use_count(), 0);
}

TEST_F(TestList, InsertFront) {
	ds::List<int> list;

	list.insert(1, ds::Position::FRONT);
	list.insert(2, ds::Position::FRONT);
	list.insert(3, ds::Position::FRONT);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 3);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 1);
	EXPECT_EQ(list.minimum(), 3);
	EXPECT_EQ(list.maximum(), 1);
}

TEST_F(TestList, InsertBack) {
	ds::List<int> list;

	list.insert(1, ds::Position::BACK);
	list.insert(2, ds::Position::BACK);
	list.insert(3, ds::Position::BACK);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);
}

TEST_F(TestList, InsertArbitrary) {
	ds::List<int> list;

	list.insert(1, ds::Position::BACK);
	list.insert(2, ds::Position::BACK);
	list.insert(3, ds::Position::BACK);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);

	list.insert(5, 2);

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 5);
	EXPECT_EQ(list.at(3), 3);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);

	list.insert(4, 1);

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);

	list.insert(6, 9999);

	EXPECT_EQ(list.size(), 6);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 6);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 6);

	list.insert(7, 5);

	EXPECT_EQ(list.size(), 7);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 7);
	EXPECT_EQ(list.at(6), 6);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 6);

	list.insert(8, 7);

	EXPECT_EQ(list.size(), 8);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 7);
	EXPECT_EQ(list.at(6), 6);
	EXPECT_EQ(list.at(7), 8);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 8);
}

TEST_F(TestList, InsertLargeList) {
	ds::List<int> list;
	int size = 10000;

	for (int i = 0; i < size; i++) {
		list.insert(i);
	}

	EXPECT_EQ(list.size(), size);
	list.clear();
	EXPECT_EQ(list.size(), 0);
}

TEST_F(TestList, InsertOutOfRange) {
	ds::List<int> list;

	list.insert(1, ds::Position::BACK);
	list.insert(2, ds::Position::BACK);
	list.insert(3, 9999999);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);
}

TEST_F(TestList, InsertOperator) {
	ds::List<int> list;

	list += 1;
	list += 2;
	list += 3;

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 3);
}

TEST_F(TestList, EqualOperator) {
	ds::List<int> list {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 5);

	list = {9, 8, 7, 6, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.minimum(), 9);
	EXPECT_EQ(list.maximum(), 5);
	EXPECT_EQ(list.at(0), 9);
	EXPECT_EQ(list.at(1), 8);
	EXPECT_EQ(list.at(2), 7);
	EXPECT_EQ(list.at(3), 6);
	EXPECT_EQ(list.at(4), 5);
}

TEST_F(TestList, ToVector) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.size(), 3);

	std::vector<int> v = list.array();
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

TEST_F(TestList, ToVectorReverse) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.size(), 3);

	std::vector<int> v = list.reverse();
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 3);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 1);
}

TEST_F(TestList, ToVectorReverseEmpty) {
	ds::List<int> list;

	std::vector<int> v = list.reverse();
	EXPECT_EQ(v.size(), 0);
}

TEST_F(TestList, Iterator) {
	ds::List<int> list {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);

	ds::List<int>::Iterator it(list.getFront().lock());

	auto it1 = list.begin();
	auto it2 = list.end();

	std::cout << "(1): " << it << ", *: " << *it << std::endl;
	std::cout << "(2): " << it.next() << ", *: " << *it << std::endl;

	std::cout << "begin: " << list.begin() << ", end: " << list.end()
			  << std::endl;

	for (auto it = list.begin(); it != list.end(); ++it) {
		std::cout << "val: " << it << ", *: " << *it << std::endl;
	}

	for (const auto &it: list) {
		std::cout << "it: " << it << std::endl;
	}

	int i = 0;
	for (it = list.begin(); it != list.end(); it++) {
		std::cout << "it: " << *it << std::endl;

		if (i == 0) {
			EXPECT_EQ(*it, 1);
		} else if (i == 1) {
			EXPECT_EQ(*it, 2);
		} else if (i == 2) {
			EXPECT_EQ(*it, 3);
		}

		i++;
	}

	it1 = list.begin();

	EXPECT_EQ(*it1, 1);
	EXPECT_EQ(*it1.next(), 2);
	EXPECT_EQ(*it1.next(), 3);
	EXPECT_EQ(*it1.next(), 4);
	EXPECT_EQ(*it1.next(), 5);
	EXPECT_EQ(*it1.next(), 0);

	list.clear();
};

TEST_F(TestList, IteratorReverse) {
	ds::List<int> list {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);

	ds::List<int>::Iterator it(list.getBack());

	auto it1 = list.rbegin();
	auto it2 = list.rend();

	std::cout << "rbegin: " << it1 << ", rend: " << it2 << std::endl;

	for (auto it = list.rbegin(); it != list.rend(); --it) {
		std::cout << "val: " << it << ", *: " << *it << std::endl;
	}

	int i = 0;
	for (it = list.rbegin(); it != list.rend(); it--) {
		std::cout << "it: " << *it << std::endl;

		if (i == 0) {
			EXPECT_EQ(*it, 5);
		} else if (i == 1) {
			EXPECT_EQ(*it, 4);
		} else if (i == 2) {
			EXPECT_EQ(*it, 3);
		}

		i++;
	}

	it1 = list.rbegin();

	EXPECT_EQ(*it1, 5);
	EXPECT_EQ(*it1.previous(), 4);
	EXPECT_EQ(*it1.previous(), 3);
	EXPECT_EQ(*it1.previous(), 2);
	EXPECT_EQ(*it1.previous(), 1);
	EXPECT_EQ(*it1.previous(), 0);

	list.clear();
}

TEST_F(TestList, Clear) {
	ds::List<int> list {1, 2, 3};

	EXPECT_EQ(list.size(), 3);
	list.clear();
	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(list.getFront().use_count(), 0);
	EXPECT_EQ(list.getBack().use_count(), 0);
	EXPECT_EQ(list.getRoot(), nullptr);
}

TEST_F(TestList, ClearOperator) {
	ds::List<int> list {1, 2, 3};

	EXPECT_EQ(list.size(), 3);
	~list;
	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(list.getFront().use_count(), 0);
	EXPECT_EQ(list.getBack().use_count(), 0);
	EXPECT_EQ(list.getRoot(), nullptr);
}

TEST_F(TestList, At) {
	ds::List<int> list {1, 2, 3};

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);

	EXPECT_THROW(list.at(999), std::out_of_range)
		<< "Can't request invalid location";

	list.clear();
}

TEST_F(TestList, ToString) {
	ds::List<int> list {1, 2, 3};
	std::string result =
		"[{\"data\":1,\"color\":\"red\"},{\"data\":2,\"color\":\"red\"},{"
		"\"data\":3,\"color\":"
		"\"red\"}]";

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.str(), result);
	EXPECT_EQ(list.json(), result);
}

TEST_F(TestList, ToStringEmpty) {
	ds::List<int> list;

	EXPECT_EQ(list.size(), 0);
	EXPECT_EQ(list.str(), "[]");
}

TEST_F(TestList, Search) {
	ds::List<int> list = {1, 2, 3};
	ds::Match<int, ds::Node> match;

	EXPECT_EQ(list.size(), 3);

	match = list.find(3);

	EXPECT_TRUE(match.getFound());
	EXPECT_EQ(match.getData(), 3);

	auto ref = match.reference();
	EXPECT_TRUE(ref != nullptr);

	match = list.find(1);

	EXPECT_TRUE(match.getFound());
	EXPECT_EQ(match.getData(), 1);
	EXPECT_TRUE(match.reference() != nullptr);

	match = list.find(2);

	EXPECT_TRUE(match.getFound());
	EXPECT_EQ(match.getData(), 2);
	EXPECT_TRUE(match.reference() != nullptr);

	match = list.find(9999);

	EXPECT_FALSE(match.getFound());
	EXPECT_EQ(match.getData(), 0);
	EXPECT_TRUE(match.reference() == nullptr);
}

template<typename T>
class TestListSearchClass {
public:

	T _data;

	TestListSearchClass(std::string &data) : _data(data) {}

	bool operator==(const TestListSearchClass &other) {
		return this->_data == other._data;
	}

	bool operator!=(const TestListSearchClass &other) {
		return this->_data != other._data;
	}

	bool operator<(const TestListSearchClass &other) {
		return other._data < this->_data;
	}

	bool operator>(const TestListSearchClass &other) {
		return other._data > this->_data;
	}
};

// TEST_F(TestList, ComplexTypeSearch) {
// 	ds::List<TestListSearchClass<std::string>> list;
// 	ds::Match<TestListSearchClass<std::string>> match;
// }

TEST_F(TestList, SearchEmpty) {
	ds::List<int> list;
	ds::Match<int, ds::Node> match;

	EXPECT_EQ(list.size(), 0);

	match = list.find(0);
	EXPECT_FALSE(match.getFound());

	match = list.find(999);
	EXPECT_FALSE(match.getFound());
}

TEST_F(TestList, Contains) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_TRUE(list.contains(1));
	EXPECT_FALSE(list.contains(7));
}

TEST_F(TestList, DeleteFront) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);

	list.removeAt(0);  // remove front of list

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.at(0), 2);
	EXPECT_EQ(list.at(1), 3);
	EXPECT_EQ(list.at(2), 4);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(**list.getRoot(), 2);
	EXPECT_EQ(list.minimum(), 2);
	EXPECT_EQ(list.maximum(), 5);

	EXPECT_EQ(list.getRoot()->getLeft(), nullptr);
}

TEST_F(TestList, DeleteBack) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);

	list.removeAt(4);  // remove front of list

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 4);

	EXPECT_EQ(list.getRoot()->getLeft(), nullptr);
}

TEST_F(TestList, DeleteArbitrary) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);

	list.removeAt(1);

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 3);
	EXPECT_EQ(list.at(2), 4);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);

	list.removeAt(1);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 5);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);
}

TEST_F(TestList, DeleteEmpty) {
	ds::List<int> list;

	EXPECT_EQ(list.size(), 0);

	EXPECT_THROW(list.removeAt(0), std::out_of_range);
	EXPECT_THROW(list.removeAt(999), std::out_of_range);
}

TEST_F(TestList, DeleteLastEntry) {
	ds::List<int> list = {1};

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 1);

	list.removeAt(0);

	EXPECT_EQ(list.size(), 0);
}

TEST_F(TestList, Initializer) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 5);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);
}

TEST_F(TestList, DeleteByValue) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);

	list.removeValue(3);

	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 5);

	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 4);
	EXPECT_EQ(list.at(3), 5);
}

TEST_F(TestList, DeleteValueError) {
	ds::List<int> list;
	EXPECT_EQ(list.size(), 0);
	EXPECT_THROW(list.removeValue(1), std::out_of_range)
		<< "Can't request invalid location";
}

TEST_F(TestList, EqualityOperator) {
	ds::List<int> l1 = {1, 2, 3, 4, 5};
	ds::List<int> l2 = {1, 2, 3, 4, 5};
	ds::List<int> l3 = {5, 4, 3, 2, 1};
	ds::List<int> l4 = {1, 3, 5};

	EXPECT_EQ(l1.size(), 5);
	EXPECT_EQ(l2.size(), 5);

	EXPECT_TRUE(l1 == l2);
	EXPECT_FALSE(l1 == l3);
	EXPECT_FALSE(l1 == l4);
}

TEST_F(TestList, InequalityOperator) {
	ds::List<int> l1 = {1, 2, 3, 4, 5};
	ds::List<int> l2 = {1, 2, 3, 4, 5};
	ds::List<int> l3 = {5, 4, 3, 2, 1};
	ds::List<int> l4 = {1, 3, 5};

	EXPECT_EQ(l1.size(), 5);
	EXPECT_EQ(l2.size(), 5);

	EXPECT_FALSE(l1 != l2);
	EXPECT_TRUE(l1 != l3);
	EXPECT_TRUE(l1 != l4);
}

TEST_F(TestList, EqualityOperatorEmpty) {
	ds::List<int> l1;
	ds::List<int> l2;

	EXPECT_EQ(l1.size(), 0);
	EXPECT_EQ(l2.size(), 0);

	EXPECT_TRUE(l1 == l2);
}

TEST_F(TestList, InequalityOperatorEmpty) {
	ds::List<int> l1;
	ds::List<int> l2;

	EXPECT_EQ(l1.size(), 0);
	EXPECT_EQ(l2.size(), 0);

	EXPECT_FALSE(l1 != l2);
}

TEST_F(TestList, Swap) {
	ds::List<int> list {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(list.size(), 7);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 7);

	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 5);
	EXPECT_EQ(list.at(5), 6);
	EXPECT_EQ(list.at(6), 7);

	list.swap(0, 0);
	list.swap(0, 6);

	EXPECT_EQ(list.size(), 7);
	EXPECT_EQ(list.minimum(), 7);
	EXPECT_EQ(list.maximum(), 1);

	EXPECT_EQ(list.at(0), 7);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 5);
	EXPECT_EQ(list.at(5), 6);
	EXPECT_EQ(list.at(6), 1);

	list.swap(4, 2);

	EXPECT_EQ(list.size(), 7);
	EXPECT_EQ(list.minimum(), 7);
	EXPECT_EQ(list.maximum(), 1);

	EXPECT_EQ(list.at(0), 7);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 5);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 6);
	EXPECT_EQ(list.at(6), 1);

	list.swap(0, 1);

	EXPECT_EQ(list.size(), 7);
	EXPECT_EQ(list.minimum(), 2);
	EXPECT_EQ(list.maximum(), 1);

	EXPECT_EQ(list.at(0), 2);
	EXPECT_EQ(list.at(1), 7);
	EXPECT_EQ(list.at(2), 5);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 6);
	EXPECT_EQ(list.at(6), 1);
}

TEST_F(TestList, BadSwap) {
	ds::List<int> list;

	EXPECT_THROW(list.swap(0, 1), std::out_of_range);
	list = {1, 2, 3, 4, 5, 6, 7};

	EXPECT_EQ(list.size(), 7);
	EXPECT_EQ(list.minimum(), 1);
	EXPECT_EQ(list.maximum(), 7);

	EXPECT_THROW(list.swap(999, 1000), std::out_of_range);
}

TEST_F(TestList, Shuffle) {
	ds::List<int> list1 {1, 2, 3, 4, 5, 6, 7, 8};
	ds::List<int> list2 = list1;
	ds::List<int> list3;

	list2.shuffle();

	EXPECT_FALSE(list1 == list2);
	EXPECT_TRUE(list1 != list2);

	std::cout << "list1:";
	for (auto it: list1) {
		std::cout << it << " " << std::endl;
	}

	std::cout << "list2:";
	for (auto it: list2) {
		std::cout << it << " " << std::endl;
	}

	EXPECT_THROW(list3.shuffle(), std::runtime_error);
}
