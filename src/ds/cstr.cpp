#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>

namespace ds {

char *dtrim(char *buf) {
	if (buf == nullptr) {
		return nullptr;
	}

	int len = strlen(buf);
	if (len == 0) {
		return buf;
	}

	// Handle trailing spaces
	int end = len - 1;
	while (end >= 0 && isspace(buf[end])) {
		end--;
	}
	buf[end + 1] = '\0';

	// Handle leading spaces
	char *start = buf;
	while (*start && isspace(*start)) {
		start++;
	}

	// If there were leading spaces, shift the string
	if (start != buf) {
		char *dst = buf;
		while (*start) {
			*dst++ = *start++;
		}
		*dst = '\0';
	}

	return buf;
}

std::string moveBufferToString(const char *buf, ssize_t size) {
	if (buf == nullptr || size <= 0) {
		return "";
	}

	std::string s(size, '\0');
	std::memcpy(&s[0], buf, size);
	return s;
}

char *removeCRLF(char *buf) {
	char *bufptr = buf;

	if (buf == nullptr) {
		return nullptr;
	}

	while (*bufptr) {
		if (*bufptr == 0x0a) {
			*bufptr = ' ';
		} else if (*bufptr == 0x0d) {
			*bufptr = ' ';
		}

		bufptr++;
	}

	return (buf);
}

char *removeIt(char *buf, const char *charsToRemove) {
	char *bufptr = buf;
	const char *rem = nullptr;
	bool removeFlag;
	unsigned int offset;

	if (buf == nullptr) {
		return nullptr;
	}

	if (charsToRemove == nullptr) {
		return buf;
	}

	offset = 0;
	removeFlag = false;
	rem = charsToRemove;

	while (*bufptr) {
		/* search the characters for the removal. */
		while ((*rem) && (!removeFlag)) {
			if (*bufptr == *rem) {
				removeFlag = true;
			}
			rem++;
		}

		if (!removeFlag) {
			buf[offset++] = *bufptr;
		}

		bufptr++;
		rem = charsToRemove;
		removeFlag = false;
	}

	buf[offset] = '\0';
	return (buf);
}

char *replaceIt(char *buf, char charToReplace, char replaceWith) {
	char *bufptr = buf;

	if (buf == nullptr) {
		return nullptr;
	}

	while (*bufptr) {
		if (*bufptr == charToReplace) {
			*bufptr = replaceWith;
		}

		bufptr++;
	}

	return (buf);
}

bool safecopy(char *dst, ssize_t dstSize, const char *src, ssize_t srcSize) {
	if (dst == nullptr or src == nullptr or dstSize <= 0 or srcSize < 0) {
		return false;
	}

	size_t numToCopy = std::min(dstSize, srcSize);
	std::memcpy(dst, src, numToCopy * sizeof(char));
	return true;
}

int tokenSplit(char *buf, const char *delimit, char **databuf, int maxTokens) {
	if (buf == nullptr || databuf == nullptr || delimit == nullptr ||
		maxTokens < 1) {
		return -1;
	}

	int index = 0;
	char *token = strtok(buf, delimit);

	while (token != nullptr && index < maxTokens) {
		databuf[index++] = token;
		token = strtok(nullptr, delimit);
	}

	return index;
}

char *upperCase(char *buf) {
	char *bufptr = nullptr;

	if (buf == nullptr) {
		return nullptr;
	}

	bufptr = buf;
	while (*bufptr) {
		*bufptr = toupper(*bufptr);
		bufptr++;
	}

	return (buf);
}

}  // namespace ds
