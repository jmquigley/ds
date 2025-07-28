#pragma once

#include <algorithm>
#include <ds/constants.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace ds {

/**
 * @brief Checks if a string contains any substring from a list
 *
 * Given a single string, use a vector of substrings to see if any string
 * within the vector is found within the input string.  Returns true any
 * time one of the substrings is found.
 *
 * @param input (`std::string`) The string to check
 * @param substrings (`std::vector<std::stirng>`) a vector of substrings to
 * search for
 * @return true If any substring from the list is found in the input string
 * @return false If none of the substrings are found in the input string
 */
bool containsAnySubstring(const std::string &input,
						  const std::vector<std::string> &substrings);

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
 * @param start A boolean flag that determines if the first character will be
 * the delimiter.  If false, then no delimiter is used.  The default is to
 * use a delimiter.
 * @param end A boolean flag that determines if the last character will be the
 * delimiter.  If false (default) no end delimiter will be used.
 * @return std::string The joined string
 */
std::string join(const std::vector<std::string> &strings,
				 const std::string &delimiter = "", bool start = true,
				 bool end = false);

/**
 * @brief Joins a vector of strings with a character delimiter
 *
 * This is a special case version of the join that takes a single character
 * and converts it into a string.  That string is then used as the same type
 * of delimiter.
 *
 * @param strings The vector of strings to join
 * @param delimiter The character to insert between each element
 * @param start A boolean flag that determines if the first character will be
 * the delimiter.  If false, then no delimiter is used.  The default is to
 * use a delimiter.
 * @param end A boolean flag that determines if the last character will be the
 * delimiter.  If false (default) no end delimiter will be used.
 * @return std::string The joined string
 */
std::string join(const std::vector<std::string> &strings, const char delimiter,
				 bool start = true, bool end = false);

/**
 * @brief Removes the first occurrence of a string from a vector
 *
 * Searches the vector for the first element that matches the target string
 * and removes it if found.
 *
 * @param v The vector of strings to search in
 * @param target The string to find and remove
 */
void removeFirstOccurrence(std::vector<std::string> &v,
						   const std::string &target);

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
