#include <ds/helpers.hpp>

namespace ds {

const size_t MAGIC1 = 5381;
const size_t MAGIC2 = 5;

auto djb2(const char *str) -> size_t {
	if (str == nullptr) {
		return 0;
	}

	size_t hash = MAGIC1;
	unsigned char c = 0;

	while ((c = *str++) != 0) {
		hash = ((hash << MAGIC2) + hash) + static_cast<size_t>(c);
	}

	return hash;
}

}  // namespace ds
