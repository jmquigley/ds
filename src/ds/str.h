#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace ds {

/**
 * Splits a string into substrings based on a list of delimiter strings.
 *
 * @param str The string to split
 * @param delimiters Vector of delimiter strings
 * @return Vector of substrings
 */
std::vector<std::string> splitStringOnDelimiters(
	const std::string &str, const std::vector<std::string> &delimiters);

}  // namespace ds
