#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace ds {

/**
 * @brief Splits a string into substrings based on a list of delimiter strings.
 *
 * This function handles multiple delimiters, consecutive delimiters, and
 * optimizes for performance with longer strings.
 *
 * @param str The string to split
 * @param delimiters Vector of delimiter strings to use for splitting
 * @param keepEmpty Whether to keep empty substrings in the result (default:
 * false)
 * @return Vector of substring components
 */
std::vector<std::string> splitStringOnDelimiters(
	const std::string &str, const std::vector<std::string> &delimiters,
	bool keepEmpty = false);

}  // namespace ds
