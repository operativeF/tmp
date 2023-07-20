//  Copyright 2018-2019 Odin Holmes.
//            2020-2023 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#pragma once

#if defined(__GNUC__) || defined(__clang__) || !defined(ENABLE_CPP_MODULE)
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#define BOOST_TMP_EXPORT
#endif // defined(__GNUC__ ) || defined(__clang__)

namespace boost::tmp {

namespace impl { // dispatch
    // dispatch : The type finds the appropriate metaclosure to invoke and forms
    // the basis of the library.
    template <std::size_t N, typename T>
    struct dispatch;
    // find_dispatch : 
    consteval std::size_t find_dispatch(std::size_t n) {
        return n <= 8 ? n :
                        n < 16 ?
                        9 :
                        n == 16 ?
                        16 :
                        n < 32 ?
                        17 :
                        n == 32 ?
                        32 :
                        n < 64 ? 33 : n == 64 ? 64 : n < 128 ? 65 : n == 128 ? 128 : 129;
    }
    // dispatch_unknown :
    template <typename C>
    struct dispatch_unknown {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
    };
    template <typename C>
    struct dispatch_unknown_v {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<Vs...>;
    };

    consteval std::size_t step_selector(std::size_t N) {
        return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
    }
} // namespace impl

// Boolean type wrapper
BOOST_TMP_EXPORT template<bool B>
struct bool_ { static constexpr bool value = B; };

// bool_ type aliases
BOOST_TMP_EXPORT using true_  = bool_<true>;
BOOST_TMP_EXPORT using false_ = bool_<false>;

// std::byte type wrapper
BOOST_TMP_EXPORT template<std::byte B>
struct byte_ { static constexpr std::byte value = B; };

// Char type wrappers
BOOST_TMP_EXPORT template<char C>
struct char_ { static constexpr char value = C; };
BOOST_TMP_EXPORT template<wchar_t C>
struct wchar_ { static constexpr wchar_t value = C; };
BOOST_TMP_EXPORT template<unsigned char C>
struct uchar_ { static constexpr unsigned char value = C; };
BOOST_TMP_EXPORT template<char8_t C>
struct char8_ { static constexpr char8_t value = C; };
BOOST_TMP_EXPORT template<char16_t C>
struct char16_ { static constexpr char16_t value = C; };
BOOST_TMP_EXPORT template<char32_t C>
struct char32_ { static constexpr char32_t value = C; };

// Unsigned and signed integral type wrappers
BOOST_TMP_EXPORT template<unsigned int V>
struct uint_ { static constexpr unsigned int value = V; };
BOOST_TMP_EXPORT template<int I>
struct int_ { static constexpr int value = I; };
BOOST_TMP_EXPORT template<std::size_t S>
struct sizet_ { static constexpr std::size_t value = S; };
BOOST_TMP_EXPORT template<std::uint8_t V>
struct uint8_ { static constexpr std::uint8_t value = V; };
BOOST_TMP_EXPORT template<std::uint16_t V>
struct uint16_ { static constexpr std::uint16_t value = V; };
BOOST_TMP_EXPORT template<std::uint32_t V>
struct uint32_ { static constexpr std::uint32_t value = V; };
BOOST_TMP_EXPORT template<std::uint64_t V>
struct uint64_ { static constexpr std::uint64_t value = V; };
BOOST_TMP_EXPORT template<std::int8_t V>
struct int8_ { static constexpr std::int8_t value = V; };
BOOST_TMP_EXPORT template<std::int16_t V>
struct int16_ { static constexpr std::int16_t value = V; };
BOOST_TMP_EXPORT template<std::int32_t V>
struct int32_ { static constexpr std::int32_t value = V; };
BOOST_TMP_EXPORT template<std::int64_t V>
struct int64_ { static constexpr std::int64_t value = V; };

// nothing_ : 
BOOST_TMP_EXPORT struct nothing_ {};

// identity_ :
BOOST_TMP_EXPORT struct identity_ {};
namespace impl { // identity_
    template <>
    struct dispatch<1, identity_> {
        template <typename T>
        using f = T;
    };
} // namespace impl

// identity_v_ :
BOOST_TMP_EXPORT template<auto V>
consteval auto identity_v_() {
    return std::forward<decltype(V)>(V);
}

// lift_ : Used for lifting a type into a function.
BOOST_TMP_EXPORT template <template <typename...> class F, typename C = identity_>
struct lift_ {};
namespace impl { // lift_
    template <template <typename...> class F, typename C>
    struct dispatch<1, lift_<F, C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<F<T>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<2, lift_<F, C>> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<F<T0, T1>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<3, lift_<F, C>> {
        template <typename T0, typename T1, typename T2>
        using f = dispatch<1, C>::template f<F<T0, T1, T2>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<4, lift_<F, C>> {
        template <typename T0, typename T1, typename T2, typename T3>
        using f = dispatch<1, C>::template f<F<T0, T1, T2, T3>>;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, lift_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<F<Ts...>>;
    };
} // namespace impl

// lift_v_ : Used for lifting a non-type parameter into a function.
BOOST_TMP_EXPORT template <template <auto...> class F, typename C = identity_>
struct lift_v_ {};
namespace impl { // lift_v_
    template <template <auto...> class F, typename C>
    struct dispatch<1, lift_v_<F, C>> {
        template <auto V>
        using f = dispatch<1, C>::template f<F<V>>;
    };
    template <template <auto...> class F, typename C>
    struct dispatch<2, lift_v_<F, C>> {
        template <auto V0, auto V1>
        using f = dispatch<1, C>::template f<F<V0, V1>>;
    };
    template <template <auto...> class F, typename C>
    struct dispatch<3, lift_v_<F, C>> {
        template <auto V0, auto V1, auto V2>
        using f = dispatch<1, C>::template f<F<V0, V1, V2>>;
    };
    template <template <auto...> class F, typename C>
    struct dispatch<4, lift_v_<F, C>> {
        template <auto V0, auto V1, auto V2, auto V3>
        using f = dispatch<1, C>::template f<F<V0, V1, V2, V3>>;
    };
    template <std::size_t N, template <auto...> class F, typename C>
    struct dispatch<N, lift_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<F<Vs...>>;
    };
} // namespace impl

// lift_v_ : Used for lifting a typename and non-type parameter(s) into a function.
BOOST_TMP_EXPORT template <template <typename, auto...> class F, typename C = identity_>
struct lift_tv_ {};
namespace impl { // lift_tv_
    template <template <typename, auto...> class F, typename C>
    struct dispatch<1, lift_tv_<F, C>> {
        template <typename T, auto V>
        using f = dispatch<1, C>::template f<F<T, V>>;
    };
    template <template <typename, auto...> class F, typename C>
    struct dispatch<2, lift_tv_<F, C>> {
        template <typename T, auto V0, auto V1>
        using f = dispatch<1, C>::template f<F<T, V0, V1>>;
    };
    template <template <typename, auto...> class F, typename C>
    struct dispatch<3, lift_tv_<F, C>> {
        template <typename T, auto V0, auto V1, auto V2>
        using f = dispatch<1, C>::template f<F<T, V0, V1, V2>>;
    };
    template <template <typename, auto...> class F, typename C>
    struct dispatch<4, lift_tv_<F, C>> {
        template <typename T, auto V0, auto V1, auto V2, auto V3>
        using f = dispatch<1, C>::template f<F<T, V0, V1, V2, V3>>;
    };
    template <std::size_t N, template <typename, auto...> class F, typename C>
    struct dispatch<N, lift_tv_<F, C>> {
        template <typename T, auto... Vs>
        using f = dispatch<1, C>::template f<F<T, Vs...>>;
    };
} // namespace impl

// list_ :
BOOST_TMP_EXPORT template <typename... Ts>
struct list_ {};
// listify_ : 
BOOST_TMP_EXPORT using listify_ = lift_<list_>;

// list_v_ :
BOOST_TMP_EXPORT template <auto... Vs>
struct list_v_ {};
// listify_v_ :
BOOST_TMP_EXPORT using listify_v_ = lift_v_<list_v_>;

template<typename T>
concept Boolable = std::convertible_to<decltype(T::value), bool>;

template<typename I>
concept Sizable = std::same_as<std::remove_cvref_t<decltype(I::value)>, std::size_t>;

template<typename F>
concept Predicatable = std::same_as<std::remove_cvref_t<decltype(F::return_type)>, bool>;

// foldey functions are internal only.
consteval std::size_t select_foldey_loop(std::size_t rest_size) {
    return static_cast<std::size_t>(rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : 1008);
}
consteval std::size_t select_foldey(std::size_t chunk_size, std::size_t rest_size, std::size_t found_at_index) {
        return found_at_index == -1 ? select_foldey_loop(rest_size) :
                                        chunk_size - found_at_index;
}

template <std::size_t S>
struct foldey {
    template <typename F, std::size_t N, typename...>
    using f = sizet_<N - S>;
};
template <>
struct foldey<1000> {
    template <typename F, std::size_t N, typename... Ts>
    using f = nothing_;
};
template <>
struct foldey<1001> {
    template <typename F, std::size_t N, typename T0, typename... Ts> 
    using f = foldey<select_foldey(1, sizeof...(Ts), F::template f<T0>::value)>::template f<F, N + 1, Ts...>;
};
template <>
struct foldey<1008> {
    template <typename F, std::size_t N, typename T0, typename T1, typename T2,
                typename T3, typename T4, typename T5, typename T6, typename T7,
                typename... Ts>
    using f = foldey<select_foldey(8, sizeof...(Ts),
                F::template
                  f<T0>::template
                    f<T1>::template
                      f<T2>::template
                        f<T3>::template
                          f<T4>::template
                            f<T5>::template
                              f<T6>::template
                                f<T7>::value)>::template
                                  f<F, N + 8, Ts...>;
};
template <>
struct foldey<1000000> {};

} // namespace boost::tmp
