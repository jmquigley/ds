#include <ds/str.h>

#include <sstream>
#include <string>
#include <vector>

namespace ds {

bool containsAnySubstring(const std::string &input,
						  const std::vector<std::string> &substrings) {
	if (input == "" || substrings.size() == 0) {
		// special case where input or vector is empty
		return false;
	}

	for (const auto &substring: substrings) {
		if (input.find(substring) != std::string::npos) {
			return true;
		}
	}

	return false;
}

std::string join(const std::vector<std::string> &strings,
				 const std::string &delimiter, bool start, bool end) {
	if (strings.empty()) {
		return "";
	}

	std::stringstream ss;

	if (start) {
		ss << delimiter;
	}

	ss << strings[0];

	for (size_t i = 1; i < strings.size(); ++i) {
		ss << delimiter << strings[i];
	}

	if (end) {
		ss << delimiter;
	}

	return ss.str();
}

std::string join(const std::vector<std::string> &strings, const char delimiter,
				 bool start, bool end) {
	std::string s {delimiter};
	return join(strings, s, start, end);
}

void removeFirstOccurrence(std::vector<std::string> &v,
						   const std::string &target) {
	// Find the first occurrence of target in the vector
	auto it = std::find(v.begin(), v.end(), target);

	// If found, remove it and return
	if (it != v.end()) {
		v.erase(it);
		return;
	}
}

std::vector<std::string> splitStringOnDelimiters(
	const std::string &str, const std::vector<std::string> &delimiters,
	bool keepEmpty) {
	std::vector<std::string> result;

	// Early return for empty input
	if (str.empty()) {
		return result;
	}

	// Handle case with no delimiters
	if (delimiters.empty()) {
		result.push_back(str);
		return result;
	}

	// Pre-calculate delimiter lengths to avoid repeated length calculations
	std::vector<size_t> delimiterLengths;
	delimiterLengths.reserve(delimiters.size());
	for (const auto &delimiter: delimiters) {
		delimiterLengths.push_back(delimiter.length());
	}

	// Reserve space for result to avoid repeated reallocations
	// Estimate capacity based on average delimiter size
	size_t estimatedParts = str.length() / 8 + 1;  // Heuristic estimate
	result.reserve(estimatedParts);

	size_t start = 0;
	while (start <= str.length()) {
		// Find the first occurrence of any delimiter
		size_t smallest_pos = std::string::npos;
		size_t delimiter_index = 0;

		for (size_t i = 0; i < delimiters.size(); ++i) {
			const auto &delimiter = delimiters[i];
			if (delimiter.empty()) {
				continue;  // Skip empty delimiters
			}

			size_t pos = str.find(delimiter, start);
			if (pos != std::string::npos &&
				(pos < smallest_pos || smallest_pos == std::string::npos)) {
				smallest_pos = pos;
				delimiter_index = i;
			}
		}

		// Process the substring
		if (smallest_pos == std::string::npos) {
			// No more delimiters found - add the last substring
			if (start < str.length() || keepEmpty) {
				result.push_back(str.substr(start));
			}
			break;
		} else {
			// Found a delimiter - add the substring before it
			if (smallest_pos > start || keepEmpty) {
				result.push_back(str.substr(start, smallest_pos - start));
			}
			start = smallest_pos + delimiterLengths[delimiter_index];
		}
	}

	return result;
}

}  // namespace ds
