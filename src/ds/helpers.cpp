#include <ds/helpers.hpp>

namespace ds {

size_t djb2(const char *str) {
	if (!str) {
		return 0;
	}

	size_t hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

}  // namespace ds
