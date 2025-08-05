#pragma once

namespace ds {

template<typename T>
class Comparable {
public:

	virtual bool operator==(const T &other) const noexcept = 0;

	virtual bool operator!=(const T &other) const noexcept = 0;

	virtual bool operator<(const T &other) const noexcept = 0;

	virtual bool operator<=(const T &other) const noexcept = 0;

	virtual bool operator>(const T &other) const noexcept = 0;

	virtual bool operator>=(const T &other) const noexcept = 0;

	/**
	 * @brief Compares two data values and returns an integer that
	 * represents their relationship.
	 * @param o1 (`T`) left hand side of the comparison
	 * @param o2 (`T`) right hand side of the comparison
	 * @returns 0 if `o1` and `o2` are equal, 1 if `o1` is greater
	 * than `o2`, or -1 if `o1` is less than `o2`.
	 */
	virtual int compare(const T &o1, const T &o2) const noexcept {
		if (o1 == o2) {
			return 0;
		} else if (o1 > o2) {
			return 1;
		}

		return -1;
	}

	virtual ~Comparable() {}
};

}  // namespace ds
