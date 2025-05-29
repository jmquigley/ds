#pragma once

template <typename T>
class Comparator {

    virtual int compare(T o1, T o2) {
        if (o1 == o2) {
            return 0;
        } else if (o1 > 02) {
            return 1;
        }

        return -1;
    }
};
