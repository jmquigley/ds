#pragma once

#include <gtest/gtest.h>

#include <string>

#include "constants.hpp"

class TestingBase : public testing::Test {
 protected:
  std::string resourceDirectory;

  TestingBase() { resourceDirectory = "./tests/resources/"; };
};
