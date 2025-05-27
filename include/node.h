#pragma once

#include <string>
#include <vector>

#include "property.h"


template <typename T>
class Node {

PROPERTY(id, Id, std::string);
PROPERTY(parentId, ParentId, std::string);

private:
    std::vector<T> children;
    Node<T> *parent;
    T data;

public:

    Node();
    Node(T data);
    ~Node();
};
