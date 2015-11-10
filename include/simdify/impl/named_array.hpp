#ifndef SIMDIFY_NAMED_ARRAY
#define SIMDIFY_NAMED_ARRAY

#include "../containers.hpp"
#include "../util/inline.hpp"
#include <array>
#include <type_traits>

namespace simd {
    enum class id {
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
    };

    namespace detail {
        template <typename T, id... Ids>
        struct id_pack;

        template <typename T>
        struct id_pack<T> {};

        template <typename T, id... Ids> struct id_pack<T, id::a, Ids...> : id_pack<T, Ids...> { T a; };
        template <typename T, id... Ids> struct id_pack<T, id::b, Ids...> : id_pack<T, Ids...> { T b; };
        template <typename T, id... Ids> struct id_pack<T, id::c, Ids...> : id_pack<T, Ids...> { T c; };
        template <typename T, id... Ids> struct id_pack<T, id::d, Ids...> : id_pack<T, Ids...> { T d; };
        template <typename T, id... Ids> struct id_pack<T, id::e, Ids...> : id_pack<T, Ids...> { T e; };
        template <typename T, id... Ids> struct id_pack<T, id::f, Ids...> : id_pack<T, Ids...> { T f; };
        template <typename T, id... Ids> struct id_pack<T, id::g, Ids...> : id_pack<T, Ids...> { T g; };
        template <typename T, id... Ids> struct id_pack<T, id::h, Ids...> : id_pack<T, Ids...> { T h; };
        template <typename T, id... Ids> struct id_pack<T, id::i, Ids...> : id_pack<T, Ids...> { T i; };
        template <typename T, id... Ids> struct id_pack<T, id::j, Ids...> : id_pack<T, Ids...> { T j; };
        template <typename T, id... Ids> struct id_pack<T, id::k, Ids...> : id_pack<T, Ids...> { T k; };
        template <typename T, id... Ids> struct id_pack<T, id::l, Ids...> : id_pack<T, Ids...> { T l; };
        template <typename T, id... Ids> struct id_pack<T, id::m, Ids...> : id_pack<T, Ids...> { T m; };
        template <typename T, id... Ids> struct id_pack<T, id::n, Ids...> : id_pack<T, Ids...> { T n; };
        template <typename T, id... Ids> struct id_pack<T, id::o, Ids...> : id_pack<T, Ids...> { T o; };
        template <typename T, id... Ids> struct id_pack<T, id::p, Ids...> : id_pack<T, Ids...> { T p; };
        template <typename T, id... Ids> struct id_pack<T, id::q, Ids...> : id_pack<T, Ids...> { T q; };
        template <typename T, id... Ids> struct id_pack<T, id::r, Ids...> : id_pack<T, Ids...> { T r; };
        template <typename T, id... Ids> struct id_pack<T, id::s, Ids...> : id_pack<T, Ids...> { T s; };
        template <typename T, id... Ids> struct id_pack<T, id::t, Ids...> : id_pack<T, Ids...> { T t; };
        template <typename T, id... Ids> struct id_pack<T, id::u, Ids...> : id_pack<T, Ids...> { T u; };
        template <typename T, id... Ids> struct id_pack<T, id::v, Ids...> : id_pack<T, Ids...> { T v; };
        template <typename T, id... Ids> struct id_pack<T, id::w, Ids...> : id_pack<T, Ids...> { T w; };
        template <typename T, id... Ids> struct id_pack<T, id::x, Ids...> : id_pack<T, Ids...> { T x; };
        template <typename T, id... Ids> struct id_pack<T, id::y, Ids...> : id_pack<T, Ids...> { T y; };
        template <typename T, id... Ids> struct id_pack<T, id::z, Ids...> : id_pack<T, Ids...> { T z; };
    }

    template <typename T, id... Ids>
    struct named_array : detail::id_pack<T, Ids...> {
        using std_array_t = std::array<T, sizeof...(Ids)>;
        using iterator = typename std_array_t::iterator;
        using const_iterator = typename std_array_t::const_iterator;
        using reverse_iterator = typename std_array_t::reverse_iterator;
        using const_reverse_iterator = typename std_array_t::const_reverse_iterator;

        SIMDIFY_FORCE_INLINE constexpr named_array() = default;
        SIMDIFY_FORCE_INLINE constexpr named_array(const named_array&) = default;
        SIMDIFY_FORCE_INLINE constexpr named_array(named_array&&) = default;

        SIMDIFY_FORCE_INLINE std_array_t& as_std_array() & { return reinterpret_cast<std_array_t&>(*this); }
        SIMDIFY_FORCE_INLINE constexpr const std_array_t& as_std_array() const& { return reinterpret_cast<const std_array_t&>(*this); }
        SIMDIFY_FORCE_INLINE std_array_t&& as_std_array() && { return reinterpret_cast<std_array_t && (*this); }
        SIMDIFY_FORCE_INLINE constexpr const std_array_t&& as_std_array() const&& { return reinterpret_cast<const std_array_t&&>(*this); }
        SIMDIFY_FORCE_INLINE T& at(std::size_t i) { return as_std_array().at(i); }
        SIMDIFY_FORCE_INLINE constexpr const T& at(std::size_t i) const { return as_std_array().at(i); }
        SIMDIFY_FORCE_INLINE T& operator[](std::size_t i) { return as_std_array()[i]; }
        SIMDIFY_FORCE_INLINE constexpr const T& operator[](std::size_t i) const { return as_std_array()[i]; }
        SIMDIFY_FORCE_INLINE constexpr const bool empty() const { return sizeof...(Ids) != 0; }
        SIMDIFY_FORCE_INLINE constexpr const std::size_t size() const { return sizeof...(Ids); }
        SIMDIFY_FORCE_INLINE void fill(const T& val) { as_std_array().fill(val); }
        SIMDIFY_FORCE_INLINE void swap(named_array& rhs) { as_std_array().swap(rhs.as_std_array()); }

        SIMDIFY_FORCE_INLINE iterator begin() { return as_std_array().begin(); }
        SIMDIFY_FORCE_INLINE iterator end() { return as_str_array().end(); }
        SIMDIFY_FORCE_INLINE constexpr const_iterator begin() const { return as_std_array().begin(); }
        SIMDIFY_FORCE_INLINE constexpr const_iterator end() const { return as_std_array().end(); }
        SIMDIFY_FORCE_INLINE constexpr const_iterator cbegin() const { return as_std_array().cbegin(); }
        SIMDIFY_FORCE_INLINE constexpr const_iterator cend() const { return as_std_array().cend(); }
        SIMDIFY_FORCE_INLINE reverse_iterator rbegin() { return as_std_array().rbegin(); }
        SIMDIFY_FORCE_INLINE reverse_iterator rend() { return as_str_array().rend(); }
        SIMDIFY_FORCE_INLINE constexpr const_reverse_iterator rbegin() const { return as_std_array().rbegin(); }
        SIMDIFY_FORCE_INLINE constexpr const_reverse_iterator rend() const { return as_std_array().rend(); }
        SIMDIFY_FORCE_INLINE constexpr const_reverse_iterator crbegin() const { return as_std_array().crbegin(); }
        SIMDIFY_FORCE_INLINE constexpr const_reverse_iterator crend() const { return as_std_array().crend(); }
    };

    template <typename T, id... Ids>
    bool operator==(const named_array<T, Ids...>& lhs, const named_array<T, Ids...>& rhs) {
        return lhs.as_std_array() == rhs.as_std_array();
    }
    template <typename T, id... Ids>
    bool operator!=(const named_array<T, Ids...>& lhs, const named_array<T, Ids...>& rhs) {
        return lhs.as_std_array() != rhs.as_std_array();
    }
}

namespace std {
    template <size_t I, typename T, simd::id... Ids>
    SIMDIFY_FORCE_INLINE constexpr T& get(simd::named_array<T, Ids...>& a) { return get<I>(a.as_std_array()); }
    template <size_t I, typename T, simd::id... Ids>
    SIMDIFY_FORCE_INLINE constexpr T&& get(simd::named_array<T, Ids...>&& a) { return get<I>(a.as_std_array()); }
    template <size_t I, typename T, simd::id... Ids>
    SIMDIFY_FORCE_INLINE constexpr const T& get(const simd::named_array<T, Ids...>& a) { return get<I>(a.as_std_array()); }
    template <size_t I, typename T, simd::id... Ids>
    SIMDIFY_FORCE_INLINE constexpr const T&& get(const simd::named_array<T, Ids...>&& a) { return get<I>(a.as_std_array()); }

    template <typename T, simd::id... Ids>
    void swap(simd::named_array<T, Ids...>& lhs, simd::named_array<T, Ids...>& rhs) { lhs.swap(rhs); }
    template <typename T, simd::id... Ids>
    struct tuple_size<simd::named_array<T, Ids...>> : integral_constant<std::size_t, sizeof...(Ids)> {};
    template <std::size_t I, typename T, simd::id... Ids>
    struct tuple_element<I, simd::named_array<T, Ids...>> { using type = T; };
}

#endif // SIMDIFY_NAMED_ARRAY
