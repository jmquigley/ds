/**
 * @brief bit flag management class
 */

#pragma once

#include <cstddef>

/**
 * @namespace ds
 * @brief Contains data structure related utilities and helper functions.
 */
namespace ds {

template<typename T>
struct BaseBitFlag {
    T flag;

    BaseBitFlag() : flag(0) {};
    BaseBitFlag(T flag) : flag(flag) {}
    BaseBitFlag(BaseBitFlag &bitFlag) {
        this->flag = bitFlag.flag;
    }

    T get() const {
        return flag;
    }

    void flipflop(T flag) {
        this->flag ^= flag;
    }

    bool has(T flag) {
        return (this->flag & flag) == flag;
    }

    void set(T flag) {
        this->flag |= flag;
    }

    void unset(T flag) {
        this->flag &= ~flag;
    }

};

typedef struct BaseBitFlag<size_t> WideBitFlag;
typedef struct BaseBitFlag<unsigned char> BitFlag;

}  // namespace ds
