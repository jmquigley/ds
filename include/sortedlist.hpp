#pragma once

#include "comparator.hpp"
#include "list.hpp"

namespace ds {

template<typename T>
class SortedList : public List<T> {
public:

	SortedList() : List<T>() {}

	SortedList(Comparator<T> comparator) : List<T>(comparator) {}

	SortedList(std::initializer_list<T> li) : List<T>(li) {}

	virtual void insert(T data) override {}
};

}  // namespace ds
