#pragma once

#include "comparator.h"
#include "node.h"
#include "property.h"
#include "stdlib.h"


template <typename T>
class Collection {

PROPERTY(first, First, T*);
PROPERTY(last, Last, T*);
PROPERTY(length, Length, size_t);

protected:
    Comparator<T> *comparator;
    Node<T> nil;
    Node<T> *root = nullptr;

public:
    Collection();
    ~Collection();

};
