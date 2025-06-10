#include <iostream>
#include <string>

#include "iterator.hpp"
#include "node.hpp"
#include "testing_base.h"

class TestIterator : public TestingBase {
protected:

	std::shared_ptr<ds::Node<int>> root;

	void SetUp() override {
		this->root = std::make_shared<ds::Node<int>>(1);
		this->root->setRight(std::make_shared<ds::Node<int>>(2));
		this->root->getRight()->setRight(std::make_shared<ds::Node<int>>(3));
	}

public:

	TestIterator() : TestingBase() {};
};

class LocalIterator : public ds::IteratorBase<int> {
public:

	LocalIterator(std::weak_ptr<ds::Node<int>> lp) : ds::IteratorBase<int>(lp) {}
};

TEST_F(TestIterator, CreateIterator) {
	LocalIterator it(root);

	std::cout << "(1): " << *it << std::endl;
	EXPECT_EQ(*it, 1);
	it.next();
	std::cout << "(2): " << *it << std::endl;
	EXPECT_EQ(*it, 2);
	it.next();
	std::cout << "(3): " << *it << std::endl;
	EXPECT_EQ(*it, 3);
};

TEST_F(TestIterator, CompareIterators) {
	LocalIterator it1(root);
	LocalIterator it2(root);

	EXPECT_TRUE(it1 == it2);
	EXPECT_FALSE(it1 != it2);
}

TEST_F(TestIterator, IteratorTestIncrement) {
	LocalIterator it(root);

	std::cout << "(1): " << *it << std::endl;
	EXPECT_EQ(*it, 1);
	it++;
	std::cout << "(2): " << *it << std::endl;
	EXPECT_EQ(*it, 2);
	it++;
	std::cout << "(3): " << *it << std::endl;
	EXPECT_EQ(*it, 3);
};
