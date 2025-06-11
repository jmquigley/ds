#pragma once

#include <type_traits>

/**
 * @namespace ds
 * @brief Contains data structure related utilities and helper functions.
 */
namespace ds {

/**
 * @brief Converts an enumeration value to its underlying integer type.
 *
 * This template function safely converts an enum class value to its underlying
 * integer representation using static_cast with type safety.
 *
 * @tparam Enumeration The enumeration type to convert from
 * @param value The enumeration value to convert
 * @return The integer representation of the enumeration value
 */
template<typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
};

}  // namespace ds
