#include <ds/str.h>

namespace ds {

std::vector<std::string> splitStringOnDelimiters(
	const std::string &str, const std::vector<std::string> &delimiters) {
	std::vector<std::string> result;

	if (str.empty()) {
		return result;
	}

	if (delimiters.size() <= 0) {
		result.push_back(str);
		return result;
	}

	size_t start = 0;
	while (start < str.length()) {
		// Find the first occurrence of any delimiter
		size_t smallest_pos = std::string::npos;
		size_t delimiter_length = 0;

		for (const auto &delimiter: delimiters) {
			size_t pos = str.find(delimiter, start);
			if (pos != std::string::npos &&
				(pos < smallest_pos || smallest_pos == std::string::npos)) {
				smallest_pos = pos;
				delimiter_length = delimiter.length();
			}
		}

		// Add the substring to the result
		if (smallest_pos == std::string::npos) {
			// No more delimiters found
			result.push_back(str.substr(start));
			break;
		} else {
			// Found a delimiter
			result.push_back(str.substr(start, smallest_pos - start));
			start = smallest_pos + delimiter_length;
		}
	}

	return result;
}

}  // namespace ds
