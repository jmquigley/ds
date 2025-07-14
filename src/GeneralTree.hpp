#pragma once

#include <BaseTree.hpp>
#include <GeneralTreeNode.hpp>

namespace ds {

template<typename T>
class GeneralTree : public BaseTree<T, GeneralTreeNode> {};

}  // namespace ds
