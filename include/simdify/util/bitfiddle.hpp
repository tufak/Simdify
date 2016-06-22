#ifndef SIMDIFY_UTIL_BITFIDDLE_HPP
#define SIMDIFY_UTIL_BITFIDDLE_HPP

#include "inline.hpp"
#include <iterator>

#if defined(__GNUC__) // GCC, Clang

namespace simd {
    // least significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL int lsb(unsigned int in) { return __builtin_ctz(in); }
    // most significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL int msb(unsigned int in) { return (8*int(sizeof(unsigned int)) - 1) - __builtin_clz(in); }
    // least significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL int lsb(unsigned long in) { return __builtin_ctzl(in); }
    // most significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL int msb(unsigned long in) { return (8*int(sizeof(unsigned long)) - 1) - __builtin_clzl(in); }
    // least significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL int lsb(unsigned long long in) { return __builtin_ctzll(in); }
    // most significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL int msb(unsigned long long in) { return (8*int(sizeof(unsigned long long)) - 1) - __builtin_clzll(in); }
    // convert little/big endian
    SIMDIFY_INL uint16_t bswap(uint16_t in) { return __builtin_bswap16(in); }
    // convert little/big endian
    SIMDIFY_INL uint32_t bswap(uint32_t in) { return __builtin_bswap32(in); }
    // convert little/big endian
    SIMDIFY_INL uint64_t bswap(uint64_t in) { return __builtin_bswap64(in); }
}

#elif defined(_MSC_VER) // Visual Studio

#include <intrin.h>

namespace simd {
    // least significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL unsigned long lsb(unsigned __int32 in) { unsigned long res; _BitScanForward(&res, in); return res; }
    // most significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL unsigned long msb(unsigned __int32 in) { unsigned long res; _BitScanReverse(&res, in); return res; }
    // convert little/big endian
    SIMDIFY_INL uint16_t bswap(uint16_t in) { return _byteswap_ushort(in); }
    // convert little/big endian
    SIMDIFY_INL uint32_t bswap(uint32_t in) { return _byteswap_ulong(in); }
    // convert little/big endian
    SIMDIFY_INL uint64_t bswap(uint64_t in) { return _byteswap_uint64(in); }

#if defined(_M_X64)
    // least significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL unsigned long lsb(unsigned __int64 in) { unsigned long res; _BitScanForward64(&res, in); return res; }
    // most significant "1" bit index; result undefined if in == 0
    SIMDIFY_INL unsigned long msb(unsigned __int64 in) { unsigned long res; _BitScanReverse64(&res, in); return res; }
#endif
}

#else

#error "util_1b.h: incompatible compiler"

#endif

namespace simd {
    
    using bit_t = uint32_t;

    // provides indices of set (1) bits, ordered from least significant to most significant
    struct bit_iterator : std::iterator<std::input_iterator_tag, bit_t> {
        bit_t mask;

        SIMDIFY_INL bit_iterator(bit_t mask_) : mask(mask_) {}
        SIMDIFY_INL bit_t operator*() const { return bit_t(lsb(mask)); }
        SIMDIFY_INL bit_t operator->() const { return bit_t(lsb(mask)); }
        SIMDIFY_INL bit_iterator& operator++() { mask = mask & (mask - 1); return *this; }
        SIMDIFY_INL bit_iterator operator++(int) { bit_iterator r = mask; operator++(); return r; }
        SIMDIFY_INL bool operator!=(const bit_iterator& rhs) const { return mask != rhs.mask; }
    };

    struct bit_field {
        bit_t field;

        SIMDIFY_INL bit_field(bit_t field_) : field(field_) {}
        SIMDIFY_INL bit_iterator begin() const { return field; }
        SIMDIFY_INL bit_iterator end() const { return 0; }
    };

}

#endif // SIMDIFY_UTIL_BITFIDDLE_HPP