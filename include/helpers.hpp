#pragma once

#include <type_traits>

namespace ds {

template<typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
};

}  // namespace ds
