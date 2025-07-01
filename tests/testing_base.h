#pragma once

#include <gmock/gmock.h>
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
		bufptr = &temp[0];

		memset(temp, 0, sizeof(temp));
		bufptr = nullptr;
	};
};
