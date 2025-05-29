#pragma once

#include "comparator.hpp"
#include "node.hpp"
#include "property.hpp"
#include "stdlib.h"

template <typename T>
class Collection {
  PROPERTY(first, First, T *);
  PROPERTY(last, Last, T *);
  PROPERTY(length, Length, size_t);

 protected:
  Comparator<T> *comparator;
  Node<T> nil;
  Node<T> *root = nullptr;

 public:
  Collection() : length(0) {}
  ~Collection() {}
};
