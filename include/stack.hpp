#pragma once

#include "collection.hpp"

template <typename T>
class Stack : protected Collection<T> {
 public:
  Stack() {}
  ~Stack() {}
};
