#include <iostream>
#include <string>
#include <vector>

#include "list.hpp"
#include "testing_base.h"

class TestList : public TestingBase {
public:

	TestList() : TestingBase() {}
};

TEST_F(TestList, ListCreate) {
	ds::List<int> list;
	EXPECT_EQ(list.getSize(), 0);

	list.insert(1);
	EXPECT_EQ(list.getSize(), 1);  // root insert

	list.insert(2);
	EXPECT_EQ(list.getSize(), 2);  // second insert

	list.insert(3);
	EXPECT_EQ(list.getSize(), 3);  // third insert

	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 3);
}

TEST_F(TestList, ListInsertFront) {
	ds::List<int> list;

	list.insert(1, ds::Position::FRONT);
	list.insert(2, ds::Position::FRONT);
	list.insert(3, ds::Position::FRONT);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.at(0), 3);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 1);
	EXPECT_EQ(**list.getFront(), 3);
	EXPECT_EQ(**list.getBack(), 1);
}

TEST_F(TestList, ListInsertBack) {
	ds::List<int> list;

	list.insert(1, ds::Position::BACK);
	list.insert(2, ds::Position::BACK);
	list.insert(3, ds::Position::BACK);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 3);
}

TEST_F(TestList, ListInsertArbitrary) {
	ds::List<int> list;

	list.insert(1, ds::Position::BACK);
	list.insert(2, ds::Position::BACK);
	list.insert(3, ds::Position::BACK);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 3);

	list.insert(5, 2);

	EXPECT_EQ(list.getSize(), 4);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 5);
	EXPECT_EQ(list.at(3), 3);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 3);

	list.insert(4, 1);

	EXPECT_EQ(list.getSize(), 5);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 3);

	list.insert(6, 9999);

	EXPECT_EQ(list.getSize(), 6);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 6);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 6);

	list.insert(7, 5);

	EXPECT_EQ(list.getSize(), 7);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 7);
	EXPECT_EQ(list.at(6), 6);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 6);

	list.insert(8, 7);

	EXPECT_EQ(list.getSize(), 8);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 2);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(list.at(4), 3);
	EXPECT_EQ(list.at(5), 7);
	EXPECT_EQ(list.at(6), 6);
	EXPECT_EQ(list.at(7), 8);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 8);
}

TEST_F(TestList, ListInsertOutOfRange) {
	ds::List<int> list;

	list.insert(1, ds::Position::BACK);
	list.insert(2, ds::Position::BACK);
	list.insert(3, 9999999);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 3);
}

TEST_F(TestList, ListToVector) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);

	std::vector<int> v = list.array();
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

TEST_F(TestList, ListToVectorReverse) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);

	std::vector<int> v = list.reverse();
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 3);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 1);
}

TEST_F(TestList, ListToVectorReverseEmpty) {
	ds::List<int> list;

	std::vector<int> v = list.reverse();
	EXPECT_EQ(v.size(), 0);
}

TEST_F(TestList, ListIterator) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);

	ds::List<int>::Iterator it(list.getFront());

	auto it1 = list.begin();
	auto it2 = list.end();

	std::cout << "(1): " << it << ", *: " << *it << std::endl;
	std::cout << "(2): " << it.next() << ", *: " << *it << std::endl;

	std::cout << "begin: " << list.begin() << ", end: " << list.end() << std::endl;

	for (auto it = list.begin(); it != list.end(); ++it) {
		std::cout << "val: " << it << ", *: " << *it << std::endl;
	}

	for (auto it: list) {
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

	list.clear();
};

TEST_F(TestList, ListIteratorReverse) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);

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
			EXPECT_EQ(*it, 3);
		} else if (i == 1) {
			EXPECT_EQ(*it, 2);
		} else if (i == 2) {
			EXPECT_EQ(*it, 1);
		}

		i++;
	}

	list.clear();
}

TEST_F(TestList, ListClear) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);
	list.clear();
	EXPECT_EQ(list.getSize(), 0);
	EXPECT_EQ(list.getFront(), nullptr);
	EXPECT_EQ(list.getBack(), nullptr);
	EXPECT_EQ(list.getRoot(), nullptr);
}

TEST_F(TestList, ListAt) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);

	EXPECT_THROW(list.at(999), std::out_of_range) << "Can't request invalid location";

	list.clear();
}

TEST_F(TestList, ListToString) {
	ds::List<int> list;
	std::string result = "[{\"data\":1},{\"data\":2},{\"data\":3}]";

	list.insert(1);
	list.insert(2);
	list.insert(3);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.str(), result);
	EXPECT_EQ(list.json(), result);
}

TEST_F(TestList, ListToStringEmpty) {
	ds::List<int> list;

	EXPECT_EQ(list.getSize(), 0);
	EXPECT_EQ(list.str(), "[]");
}

TEST_F(TestList, ListSearch) {
	ds::List<int> list;
	ds::Match<int> match;

	list.insert(1);
	list.insert(2);
	list.insert(3);
	EXPECT_EQ(list.getSize(), 3);

	match = list.find(3);

	EXPECT_TRUE(match.getFound());
	EXPECT_EQ(match.getData(), 3);
	EXPECT_EQ(match.getIndex(), 2);

	match = list.find(1);

	EXPECT_TRUE(match.getFound());
	EXPECT_EQ(match.getData(), 1);
	EXPECT_EQ(match.getIndex(), 0);

	match = list.find(9999);

	EXPECT_FALSE(match.getFound());
	EXPECT_EQ(match.getData(), 0);
	EXPECT_EQ(match.getIndex(), 0);
}

TEST_F(TestList, ListSearchEmpty) {
	ds::List<int> list;
	ds::Match<int> match;

	EXPECT_EQ(list.getSize(), 0);

	match = list.find(0);
	EXPECT_FALSE(match.getFound());

	match = list.find(999);
	EXPECT_FALSE(match.getFound());
}

TEST_F(TestList, ListDeleteFront) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.insert(5);

	EXPECT_EQ(list.getSize(), 5);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 5);

	list.remove(0);	 // remove front of list

	EXPECT_EQ(list.getSize(), 4);
	EXPECT_EQ(list.at(0), 2);
	EXPECT_EQ(list.at(1), 3);
	EXPECT_EQ(list.at(2), 4);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(**list.getRoot(), 2);
	EXPECT_EQ(**list.getFront(), 2);
	EXPECT_EQ(**list.getBack(), 5);

	EXPECT_EQ(list.getRoot()->getLeft(), nullptr);
}

TEST_F(TestList, ListDeleteBack) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.insert(5);

	EXPECT_EQ(list.getSize(), 5);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 5);

	list.remove(4);	 // remove front of list

	EXPECT_EQ(list.getSize(), 4);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 4);

	EXPECT_EQ(list.getRoot()->getLeft(), nullptr);
}

TEST_F(TestList, ListDeleteArbitrary) {
	ds::List<int> list;

	list.insert(1);
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.insert(5);

	EXPECT_EQ(list.getSize(), 5);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 5);

	list.remove(1);

	EXPECT_EQ(list.getSize(), 4);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 3);
	EXPECT_EQ(list.at(2), 4);
	EXPECT_EQ(list.at(3), 5);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 5);

	list.remove(1);

	EXPECT_EQ(list.getSize(), 3);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 4);
	EXPECT_EQ(list.at(2), 5);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 5);
}

TEST_F(TestList, ListDeleteEmpty) {
	ds::List<int> list;

	EXPECT_EQ(list.getSize(), 0);

	list.remove(0);
	list.remove(9999);
}

TEST_F(TestList, ListInitializer) {
	ds::List<int> list = {1, 2, 3, 4, 5};

	EXPECT_EQ(list.getSize(), 5);
	EXPECT_EQ(list.at(0), 1);
	EXPECT_EQ(list.at(1), 2);
	EXPECT_EQ(list.at(2), 3);
	EXPECT_EQ(list.at(3), 4);
	EXPECT_EQ(list.at(4), 5);
	EXPECT_EQ(**list.getRoot(), 1);
	EXPECT_EQ(**list.getFront(), 1);
	EXPECT_EQ(**list.getBack(), 5);
}
