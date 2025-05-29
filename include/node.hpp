#pragma once

#include <uuid/uuid.h>

#include <iostream>
#include <string>
#include <vector>

#include "property.hpp"

template <typename T>
class Node {
  PROPERTY(id, Id, std::string);
  PROPERTY(parentId, ParentId, std::string);

 private:
  std::vector<T> children;
  Node<T> *parent;
  T data;

 public:
  Node() {
    uuid_t uuid;
    char uuidStr[UUID_STR_LEN];

    uuid_generate_random(uuid);
    uuid_unparse(uuid, uuidStr);
    id = uuidStr;

    std::cout << "UUID: '" << id << "'" << std::endl;
  }

  Node(T data) : data(data), Node() {}
  ~Node() {}
};
