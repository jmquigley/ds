#pragma once

#include <gtest/gtest.h>

#include <string>

#include "testing_base.h"

class TestNode : public TestingBase {
 protected:
  char temp[constants::BUFSIZE];
  char* bufptr;

  TestNode();
};
