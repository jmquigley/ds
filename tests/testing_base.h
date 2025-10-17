#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ds/Comparable.hpp>
#include <ds/constants.hpp>
#include <ds/property.hpp>
#include <format>
#include <iostream>
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

/**
 * @brief Specialized class that contains all Comparable information for testing
 *
 * This class is used in all testing routines to satify all comparison operations
 * that are needed for LRU and collection operations.
 *
 */
class TestSearchClass : public ds::Comparable<TestSearchClass> {
	PROPERTY_WITH_DEFAULT(data, Data, std::string, {});

public:

	TestSearchClass() = default;

	TestSearchClass(const std::string &data) : _data(data) {}

	~TestSearchClass() override = default;

	auto operator==(const TestSearchClass &other) const noexcept -> bool override {
		return this->_data == other._data;
	}

	auto operator!=(const TestSearchClass &other) const noexcept -> bool override {
		return this->_data != other._data;
	}

	auto operator<(const TestSearchClass &other) const noexcept -> bool override {
		return this->_data < other._data;
	}

	auto operator>(const TestSearchClass &other) const noexcept -> bool override {
		return this->_data > other._data;
	}

	auto operator<=(const TestSearchClass &other) const noexcept -> bool override {
		return this->_data <= other._data;
	}

	auto operator>=(const TestSearchClass &other) const noexcept -> bool override {
		return this->_data >= other._data;
	}

	auto print(std::ostream &os) const ->void override {
		os << this->_data;
	}
};

namespace std {
template<>
struct hash<TestSearchClass> {
	size_t operator()(const TestSearchClass &search) const {
	return hash<std::string>()(search.data());
	}
};
}  // namespace std
