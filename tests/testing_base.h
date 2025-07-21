#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ds/constants.hpp>
#include <ds/property.hpp>
#include <format>
#include <string>

class TestingBase : public testing::Test {

    /**
     * @brief the directory location where testing resources/files can be found
     */
    PROPERTY_SCOPED(resourceDirectory, ResourceDirectory, std::string, protected:);

protected:

	char temp[constants::BUFSIZE];
	char *bufptr = nullptr;

	TestingBase() : _resourceDirectory(std::format("{}/", TEST_DATA_DIR)) {
		bufptr = &temp[0];
		memset(temp, 0, sizeof(temp));
		bufptr = nullptr;
	};
};
