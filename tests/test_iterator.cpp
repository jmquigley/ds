#include <testing_base.h>

#include <ds/BaseIterator.hpp>
#include <ds/Node.hpp>
#include <iostream>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

class TestIterator : public TestingBase {
protected:

	std::shared_ptr<ds::Node<int>> root;
	std::shared_ptr<ds::Node<int>> n1;
	std::shared_ptr<ds::Node<int>> n2;
	std::shared_ptr<ds::Node<int>> n3;

	auto SetUp() -> void override {
		n1 = std::make_shared<ds::Node<int>>(1);
		n2 = std::make_shared<ds::Node<int>>(2);
		n3 = std::make_shared<ds::Node<int>>(3);

		n1->setRight(n2);
		n2->setRight(n3);
		n2->setLeft(n1);
		n3->setLeft(n2);

		this->root = n1;
	}

	void TearDown() override {
		n3->clear();
		n2->clear();
		n1->clear();
		root.reset();
	}

	static void validateRootIterator(ds::BaseIterator<int, ds::Node> &it) {
		std::cout << "it(1): " << *it << std::endl;
		EXPECT_EQ(*it, 1);
		it.next();
		std::cout << "it(2): " << *it << std::endl;
		EXPECT_EQ(*it, 2);
		it.next();
		std::cout << "it(3): " << *it << std::endl;
		EXPECT_EQ(*it, 3);
	}

public:

	TestIterator() = default;
};

class LocalIterator : public ds::BaseIterator<int, ds::Node> {
public:

	LocalIterator(std::weak_ptr<ds::Node<int>> lp)
		: ds::BaseIterator<int, ds::Node>(lp) {}

	LocalIterator() = default;
};

TEST_F(TestIterator, Create) {
	LocalIterator it(root);
	validateRootIterator(it);
};

TEST_F(TestIterator, CopyConstructor) {
	LocalIterator it1(root);
	LocalIterator it2(it1);

	EXPECT_TRUE(it1 == it2);

	validateRootIterator(it1);
	validateRootIterator(it2);
}

TEST_F(TestIterator, MoveConstructor) {
	LocalIterator it1(root);
	LocalIterator it2(std::move(it1));
	validateRootIterator(it2);
	EXPECT_TRUE(it1.lp().expired());
}

TEST_F(TestIterator, AssignmentOperators) {
	// Assignment operator
	LocalIterator it1(root);
	LocalIterator it2;

	it2 = it1;
	validateRootIterator(it2);

	// Move assignment operator
	LocalIterator it3(root);
	it2 = std::move(it3);
	validateRootIterator(it2);
	EXPECT_TRUE(it3.lp().expired());
}

TEST_F(TestIterator, CompareIterators) {
	LocalIterator it1(root);
	LocalIterator it2(root);

	EXPECT_TRUE(it1 == it2);
	EXPECT_FALSE(it1 != it2);
}

TEST_F(TestIterator, CompareIteratorsOpposite) {
	LocalIterator it1(n1);
	LocalIterator it2(n2);

	EXPECT_FALSE(it1 == it2);
	EXPECT_TRUE(it1 != it2);
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
}

TEST_F(TestIterator, IteratorTestDecrement) {
	LocalIterator it(root->getRight()->getRight());

	std::cout << "(1): " << *it << std::endl;
	EXPECT_EQ(*it, 3);
	it--;
	std::cout << "(2): " << *it << std::endl;
	EXPECT_EQ(*it, 2);
	it--;
	std::cout << "(3): " << *it << std::endl;
	EXPECT_EQ(*it, 1);
}

TEST_F(TestIterator, Empty) {
	LocalIterator it;
	EXPECT_EQ(*it, 0);
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
