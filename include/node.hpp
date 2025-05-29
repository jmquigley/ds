#pragma once

#include <uuid/uuid.h>

#include <iostream>
#include <string>
#include <vector>

#include "property.hpp"

template <typename T>
class Node {
  PROPERTY_READONLY(data, Data, T);
  PROPERTY_READONLY(id, Id, std::string);

  PROPERTY(left, Left, Node<T> *);
  PROPERTY(parent, Parent, Node<T> *);
  PROPERTY(parentId, ParentId, std::string);
  PROPERTY(right, Right, Node<T> *);

 private:
  std::vector<T> children;

 void init() {
    uuid_t uuid;
    char uuidStr[UUID_STR_LEN];

    // Creates a unique identifier for a node
    uuid_generate_random(uuid);
    uuid_unparse(uuid, uuidStr);
    id = uuidStr;
 }

 public:
  Node(): left(nullptr), right(nullptr), parent(nullptr) {
      init();
  }

  Node(T data) : data(data), Node() {}
  Node(std::string parentID, T data) : data(data), parentId(parentId), Node() {}
  ~Node() {}

  void clear() {
      // TODO: add implementation for the clear() in Node
  }

  std::string str() {
      // TODO: add implementation for str() in Node
      return "";
  }

};
