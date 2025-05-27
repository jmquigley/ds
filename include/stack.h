#pragma once

#include "collection.h"

template <typename T>
class Stack: protected Collection<T> {

public:
    Stack();
    ~Stack();
};
