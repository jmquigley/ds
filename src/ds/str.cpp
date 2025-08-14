#include <ds/str.h>

#include <sstream>
#include <string>
#include <vector>

namespace ds {

auto containsAnySubstring(const std::string &input,
						  const std::vector<std::string> &substrings) -> bool {
	if (input.empty() || substrings.empty()) {
		// special case where input or vector is empty
		return false;
	}

	return std::ranges::any_of(substrings,
							   [&input](const auto &substring) -> auto {
		return input.find(substring) != std::string::npos;
	});
}

auto join(const std::vector<std::string> &strings, const std::string &delimiter,
		  bool start, bool end) -> std::string {
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

auto join(const std::vector<std::string> &strings, char delimiter, bool start,
		  bool end) -> std::string {
	std::string s {delimiter};
	return join(strings, s, start, end);
}

auto removeFirstOccurrence(std::vector<std::string> &v,
						   const std::string &target) -> void {
	// Find the first occurrence of target in the vector
	auto it = std::ranges::find(v, target);

	// If found, remove it and return
	if (it != v.end()) {
		v.erase(it);
		return;
	}
}

auto splitStringOnDelimiters(const std::string &str,
							 const std::vector<std::string> &delimiters,
							 bool keepEmpty) -> std::vector<std::string> {
	// Constants to avoid magic numbers
	constexpr size_t npos = std::string::npos;
	constexpr size_t avg_token_size = 5;  // Average expected token size

	std::vector<std::string> result;

	// Handle empty cases
	if (str.empty()) {
		return result;
	}
	if (delimiters.empty()) {
		result.push_back(str);
		return result;
	}

	// Pre-calculate delimiter lengths
	std::vector<size_t> delimLengths;
	delimLengths.reserve(delimiters.size());
	for (const auto &delim: delimiters) {
		delimLengths.push_back(delim.length());
	}

	// Reserve space for result (rough estimate)
	result.reserve((str.length() / avg_token_size) + 1);

	size_t start = 0;
	bool continue_processing = true;

	while (start <= str.length() && continue_processing) {
		// Find earliest delimiter
		size_t pos = npos;
		size_t delimIdx = 0;

		for (size_t i = 0; i < delimiters.size(); ++i) {
			if (delimiters[i].empty()) {
				continue;
			}

			size_t currentPos = str.find(delimiters[i], start);
			if (currentPos != npos && (currentPos < pos || pos == npos)) {
				pos = currentPos;
				delimIdx = i;
			}
		}

		// No more delimiters
		if (pos == npos) {
			if (start < str.length() || keepEmpty) {
				result.push_back(str.substr(start));
			}
			continue_processing = false;
		} else {
			// Add substring before delimiter
			if (pos > start || keepEmpty) {
				result.push_back(str.substr(start, pos - start));
			}

			start = pos + delimLengths[delimIdx];
		}
	}

	return result;
}

}  // namespace ds
