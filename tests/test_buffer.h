#pragma once

#include <gtest/gtest.h>
#include <testing_base.h>

#include <string>

class TestBuffer : public TestingBase {
protected:

	std::string infile;

	TestBuffer();
};
