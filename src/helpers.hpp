#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>

namespace ds {

/**
 * @brief Checks if all provided pointer-like objects are valid (non-null)
 * with short-circuit evaluation
 * @returns true if all values are valid, otherwise false
 */
template<typename P, typename... Ptrs>
[[nodiscard]] constexpr inline bool all(const P &p,
										const Ptrs &...ptrs) noexcept {
	if (!bool(p)) {
		return false;
	}
	if constexpr (sizeof...(ptrs) == 0) {
		return true;
	} else {
		return all(ptrs...);
	}
}

/**
 * @brief Checks if any of the provided pointer-like objects are valid
 * (non-null) with short-circuit evaluation
 * @returns true if any pointer in the list is valid, otherwise false.
 */
template<typename P, typename... Ptrs>
[[nodiscard]] constexpr inline bool any(const P &p,
										const Ptrs &...ptrs) noexcept {
	if (bool(p)) {
		return true;
	}
	if constexpr (sizeof...(ptrs) == 0) {
		return false;
	} else {
		return any(ptrs...);
	}
}

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
auto as_integer(Enumeration const value) ->
	typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
};

/**
 * @brief Converts a shared pointer to a string representation
 *
 * This function extracts the raw memory address of the object pointed to by
 * the shared pointer and converts it to a string representation, typically
 * in hexadecimal format.
 *
 * @tparam T The type of object pointed to by the shared pointer
 * @param p The shared pointer to convert to a string
 * @return A string representation of the pointer's memory address
 */
template<typename T>
std::string pointerToString(std::shared_ptr<T> p) {
	std::stringstream ss;
	void *rawAddress = static_cast<void *>(p.get());
	ss << rawAddress;
	return ss.str();
}

/**
 * @brief Converts a weak pointer to a string representation
 *
 * This function attempts to lock the weak pointer and obtain a string
 * representation of the pointed-to object. If the weak pointer is expired
 * (i.e., the object has been deleted), it returns "invalid".
 *
 * @tparam T The type of object pointed to by the weak pointer
 * @param wp The weak pointer to convert to a string
 * @param message The message to return when the pointer is invalid
 * @return A string representation of the pointer address or "invalid" if
 * expired
 */
template<typename T>
std::string weakPointerToString(std::weak_ptr<T> wp,
								std::string message = "invalid") {
	std::shared_ptr<T> p = wp.lock();

	if (p) {
		return pointerToString(p);
	}

	return message;
}

}  // namespace ds
