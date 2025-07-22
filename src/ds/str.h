#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace ds {

/**
 * @brief Joins a vector of strings with a specified delimiter
 *
 * @code
 *   std::vector<std::string> words = {"Hello", "world"};
 *   std::string result1 = join(words);       // "Helloworld"
 *   std::string result2 = join(words, ", "); // "Hello, world"
 * @endcode
 * @param strings The vector of strings to join
 * @param delimiter The string to insert between each element (defaults to empty
 * string)
 * @param end A boolean flag that determines if the last character will be the
 * delimiter.  If false (default) no end delimiter will be used.
 * @return std::string The joined string
 */
std::string join(const std::vector<std::string> &strings,
				 const std::string &delimiter = "", bool end = false);

/**
 * @brief Splits a string into substrings based on a list of delimiter
 * strings.
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
