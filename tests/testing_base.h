#pragma once

#include <gtest/gtest.h>

#include <string>

#include "constants.hpp"

class TestingBase : public testing::Test {
protected:

	std::string resourceDirectory;
	char temp[constants::BUFSIZE];
	char *bufptr = nullptr;

	TestingBase() {
		resourceDirectory = "./tests/resources/";
	};
};
