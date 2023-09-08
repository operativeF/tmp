//  Copyright 2018-2019 Odin Holmes.
//            2020-2023 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef __BOOST_TMP_BASE_HPP
#define __BOOST_TMP_BASE_HPP

#if defined(__GNUC__) || defined(__clang__) || !defined(ENABLE_CPP_MODULE)
#include <concepts>
#include <type_traits>
#define BOOST_TMP_EXPORT
#endif // defined(__GNUC__ ) || defined(__clang__)

namespace boost::tmp {

using int8_t   = signed char;
using int16_t  = short;
using int32_t  = int;
using int64_t  = long long;
using uint8_t  = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using uint64_t = unsigned long long;

#ifdef _WIN64
    using size_t    = uint64_t;
    using ptrdiff_t = int64_t;
    using intptr_t  = int64_t;
#else
    using size_t    = unsigned int;
    using ptrdiff_t = int;
    using intptr_t  = int;
#endif

namespace impl { // dispatch
    // dispatch : The type finds the appropriate metaclosure to invoke and forms
    // the basis of the library.
    template <size_t N, typename T>
    struct dispatch;
    // find_dispatch : 
    consteval size_t find_dispatch(size_t n) {
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

    consteval size_t step_selector(size_t N) {
        return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
    }
} // namespace impl

// Boolean type wrapper
BOOST_TMP_EXPORT template<bool B>
struct bool_ { static constexpr bool value = B; };

// bool_ type aliases
BOOST_TMP_EXPORT using true_  = bool_<true>;
BOOST_TMP_EXPORT using false_ = bool_<false>;

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
BOOST_TMP_EXPORT template<size_t S>
struct sizet_ { static constexpr size_t value = S; };
BOOST_TMP_EXPORT template<uint8_t V>
struct uint8_ { static constexpr uint8_t value = V; };
BOOST_TMP_EXPORT template<uint16_t V>
struct uint16_ { static constexpr uint16_t value = V; };
BOOST_TMP_EXPORT template<uint32_t V>
struct uint32_ { static constexpr uint32_t value = V; };
BOOST_TMP_EXPORT template<uint64_t V>
struct uint64_ { static constexpr uint64_t value = V; };
BOOST_TMP_EXPORT template<int8_t V>
struct int8_ { static constexpr int8_t value = V; };
BOOST_TMP_EXPORT template<int16_t V>
struct int16_ { static constexpr int16_t value = V; };
BOOST_TMP_EXPORT template<int32_t V>
struct int32_ { static constexpr int32_t value = V; };
BOOST_TMP_EXPORT template<int64_t V>
struct int64_ { static constexpr int64_t value = V; };

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
    template <size_t N, template <typename...> class F, typename C>
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
    template <size_t N, template <auto...> class F, typename C>
    struct dispatch<N, lift_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<F<Vs...>>;
    };
} // namespace impl

// lift_tv_ : Used for lifting a typename and non-type parameter(s) into a function.
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
    template <size_t N, template <typename, auto...> class F, typename C>
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
concept Sizable = std::same_as<std::remove_cvref_t<decltype(I::value)>, size_t>;

template<typename F>
concept Predicatable = std::same_as<std::remove_cvref_t<decltype(F::return_type)>, bool>;

// foldey functions are internal only.
consteval size_t select_foldey_loop(size_t rest_size) {
    return static_cast<size_t>(rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : 1008);
}
consteval size_t select_foldey(size_t chunk_size, size_t rest_size, size_t found_at_index) {
        return found_at_index == -1 ? select_foldey_loop(rest_size) :
                                        chunk_size - found_at_index;
}

template <size_t S>
struct foldey {
    template <typename F, size_t N, typename...>
    using f = sizet_<N - S>;
};
template <>
struct foldey<1000> {
    template <typename F, size_t N, typename... Ts>
    using f = nothing_;
};
template <>
struct foldey<1001> {
    template <typename F, size_t N, typename T0, typename... Ts> 
    using f = foldey<select_foldey(1, sizeof...(Ts), F::template f<T0>::value)>::template f<F, N + 1, Ts...>;
};
template <>
struct foldey<1008> {
    template <typename F, size_t N, typename T0, typename T1, typename T2,
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

// call_ : a foundational metaclosure that immediately evaluates the input metaclosure(s).
BOOST_TMP_EXPORT template <typename F, typename... Ts>
using call_ = impl::dispatch<impl::find_dispatch(sizeof...(Ts)), F>::template f<Ts...>;
BOOST_TMP_EXPORT template <typename T, typename... Ts>
using call_t = impl::dispatch<impl::find_dispatch(sizeof...(Ts)), T>::template
                    f<Ts...>::type;

// call_f_ : 
BOOST_TMP_EXPORT template <typename C = identity_>
struct call_f_ {};
namespace impl { // call_f_
    template <size_t N, typename C>
    struct dispatch<N, call_f_<C>> {
        template <typename F, typename... Ts>
        using f = dispatch<1, C>::template f<
                        typename dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>>;
    };
} // namespace impl

// \brief turns a list of types into a variadic pack of those types /
// example: call<all<>,true_,false_,true_> is equivalent to
// call<unpack<all<>>,list<true_,false_,true_>>
// \requirement
// Unpack always needs a continuation, so even if you're just unpacking
// a list, you need to use it like the following:
// using alist = list_<uint_<0>>;
// uint_<0>{} = call_<unpack_<identity_>, alist>{}; // This will be vaild
BOOST_TMP_EXPORT template <typename C>
struct unpack_ {};
namespace impl { // unpack_
    template <typename C, typename L>
    struct unpack_impl;
    template <typename C, template <typename...> class Seq, typename... Ls>
    struct unpack_impl<C, Seq<Ls...>> {
        using type = dispatch<find_dispatch(sizeof...(Ls)), C>::template f<Ls...>;
    };
    // in case of nothing_ input give a nothing_ output
    template <typename C>
    struct unpack_impl<C, nothing_> {
        using type = nothing_;
    };
    template <typename C>
    struct dispatch<1, unpack_<C>> {
        template <typename L>
        using f = unpack_impl<C, L>::type;
    };
} // namespace impl

} // namespace boost::tmp

#endif // __BOOST_TMP_BASE_HPP
