#pragma once

#include <gtest/gtest.h>

#include <string>

#include "constants.h"

class TestingBase : public testing::Test {
 protected:
  std::string resourceDirectory;

  TestingBase() { resourceDirectory = "./tests/resources/"; };
};
