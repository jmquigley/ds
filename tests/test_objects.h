#pragma once

#include <gtest/gtest.h>

#include <string>

#include "testing_base.h"

//
// Holds the base class for each test case suite


class TestComparator : public TestingBase {
public:

	TestComparator();
};

class TestList : public TestingBase {
public:

	TestList();
};

class TestNode : public TestingBase {
public:

	TestNode();
};

class TestStack : public TestingBase {
protected:

	TestStack();
};
