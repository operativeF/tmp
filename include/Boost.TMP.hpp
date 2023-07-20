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

#include "Boost.TMP.Base.hpp"

namespace boost::tmp {

// always_ : metaclosure returns type / shovels into the continuation C.
BOOST_TMP_EXPORT template <typename T, typename C = identity_>
struct always_ {};
namespace impl { // always_
    template <std::size_t N, typename T, typename C>
    struct dispatch<N, always_<T, C>> {
        template <typename...>
        using f = dispatch<1, C>::template f<T>;
    };
} // namespace impl

// result_: The same as always_, but refers to the type inside
// of the input type T.
BOOST_TMP_EXPORT template <typename C = identity_>
struct result_ {};
namespace impl { // result_
    template <typename C>
    struct dispatch<1, result_<C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<T::type>;
    };
} // namespace impl

namespace impl { // maybe_
    template <bool B>
    struct maybe_test_ {
        template <typename T>
        using f = T;
    };
    template <>
    struct maybe_test_<true> {};
    template <typename T> // TODO: Get rid of std::is_same_v here.
    using maybe_impl = maybe_test_<std::is_same_v<T, nothing_>>::template f<T>;
} // namespace impl
BOOST_TMP_EXPORT template <typename T, typename... Ts>
using maybe_ = impl::maybe_impl<typename impl::dispatch<impl::find_dispatch(sizeof...(Ts)), T>::template
                    f<Ts...>>;
BOOST_TMP_EXPORT template <typename T, typename... Ts>
using maybe_t = impl::maybe_impl<typename impl::dispatch<impl::find_dispatch(sizeof...(Ts)), T>::template
                    f<Ts...>::type>;

// each_ :
BOOST_TMP_EXPORT template <typename... Fs>
struct each_ {};
namespace impl { // each_
    template <typename F, typename C>
    struct dispatch<1, each_<F, C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<dispatch<1, F>::template f<T>>;
    };
    template <typename F0, typename F1, typename C>
    struct dispatch<2, each_<F0, F1, C>> {
        template <typename T0, typename T1>
        using f = dispatch<2, C>::template f<dispatch<1, F0>::template f<T0>,
                                                dispatch<1, F1>::template f<T1>>;
    };
    template <typename F0, typename F1, typename F2, typename C>
    struct dispatch<3, each_<F0, F1, F2, C>> {
        template <typename T0, typename T1, typename T2>
        using f = dispatch<3, C>::template f<dispatch<1, F0>::template f<T0>,
                                                dispatch<1, F1>::template f<T1>,
                                                dispatch<1, F2>::template f<T2>>;
    };
    template <typename F0, typename F1, typename F2, typename F3, typename C>
    struct dispatch<4, each_<F0, F1, F2, F3, C>> {
        template <typename T0, typename T1, typename T2, typename T3>
        using f = dispatch<4, C>::template f<dispatch<1, F0>::template f<T0>,
                                                dispatch<1, F1>::template f<T1>,
                                                dispatch<1, F2>::template f<T2>,
                                                dispatch<1, F3>::template f<T3>>;
    };
} // namespace impl

// filter_ :
BOOST_TMP_EXPORT template <typename F, typename C = listify_>
struct filter_ {};
namespace impl { // filter_
    template <std::size_t N, template <typename...> class F, typename C>
    struct filtery;
    template <template <typename...> class F, typename C>
    struct filtery<0, F, C> {
        template <std::size_t N, typename T, typename U, typename... Ts>
        using f = filtery<(F<U>::value + 2 * (N == 1)), F,
                                    C>::template f<(N - 1), U, Ts...>;
    };
    template <template <typename...> class F, typename C>
    struct filtery<1, F, C> {
        template <std::size_t N, typename T, typename U, typename... Ts>
        using f = filtery<(F<U>::value + 2 * (N == 1)), F, C>::template
                        f<(N - 1), U, Ts..., T>;
    };
    template <template <typename...> class F, typename C>
    struct filtery<2, F, C> { // all the way around, remove last
        template <std::size_t N, typename T, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
    };
    template <template <typename...> class F, typename C>
    struct filtery<3, F, C> { // all the way around, keep last
        template <std::size_t N, typename T, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, filter_<lift_<F>, C>> {
        template <typename T, typename... Ts>
        using f = filtery<(F<T>::value + 2 * (sizeof...(Ts) == 0)), F,
                                    C>::template f<(sizeof...(Ts)), T, Ts...>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, filter_<F, C>> {
        template <typename T, typename... Ts>
        using f = filtery<
                (dispatch<1, F>::template f<T>::value + 2 * (sizeof...(Ts) == 0)),
                dispatch<1, F>::template f, C>::template f<(sizeof...(Ts)), T, Ts...>;
    };
    template <typename F, typename C>
    struct dispatch<0, filter_<F, C>> {
        template <typename... Ts>
        using f = dispatch<0, C>::template f<>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<0, filter_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<0, C>::template f<>;
    };
} // namespace impl

/// fold_left_ : folds left over a list using a binary predicate /
/// fold left considers the first element in the input pack the initial state, use
/// `push_front_<>` to add initial state if needed
/// Multiple input, single output
// fold_left_ : 
BOOST_TMP_EXPORT template <typename F = listify_, typename C = identity_>
struct fold_left_ {};
namespace impl { // fold_left_
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<0, fold_left_<lift_<F>, lift_<C>>> {
        template <typename...>
        using f = nothing_;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<1, fold_left_<lift_<F>, lift_<C>>> {
        template <typename T>
        using f = C<T>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<2, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0>
        using f = C<F<In, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<3, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1>
        using f = C<F<F<In, T0>, T1>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<4, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1, typename T2>
        using f = C<F<F<F<In, T0>, T1>, T2>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<5, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1, typename T2, typename T3>
        using f = C<F<F<F<F<In, T0>, T1>, T2>, T3>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<6, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1, typename T2, typename T3,
                typename T4>
        using f = C<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<7, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5>
        using f = C<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<8, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6>
        using f = C<F<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>, T6>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<9, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In, typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                                    fold_left_<lift_<F>, lift_<C>>>::
                template f<F<F<F<F<F<F<F<In, T0>, T1>, T2>, T3>, T4>, T5>, T6>, Ts...>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<16, fold_left_<lift_<F>, lift_<C>>> {
        template <typename In,  typename T0,  typename T1,  typename T2,  typename T3,
                typename T4,  typename T5,  typename T6,  typename T7,  typename T8,
                typename T9,  typename T10, typename T11, typename T12, typename T13,
                typename T14, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), fold_left_<lift_<F>, lift_<C>>>::template
                    f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In,
                                                    T0>,
                                                    T1>,
                                                T2>,
                                                T3>,
                                            T4>,
                                            T5>,
                                        T6>,
                                        T7>,
                                    T8>,
                                    T9>,
                                T10>,
                                T11>,
                            T12>,
                            T13>,
                        T14>,
                        Ts...>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<17, fold_left_<lift_<F>, lift_<C>>>
        : dispatch<16, fold_left_<lift_<F>, lift_<C>>> {};
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<32, fold_left_<lift_<F>, lift_<C>>> {
        template<typename In,  typename T0,  typename T1,  typename T2,  typename T3,
                typename T4,  typename T5,  typename T6,  typename T7,  typename T8,
                typename T9,  typename T10, typename T11, typename T12, typename T13,
                typename T14, typename T15, typename T16, typename T17, typename T18,
                typename T19, typename T20, typename T21, typename T22, typename T23,
                typename T24, typename T25, typename T26, typename T27, typename T28,
                typename T29, typename T30, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                    fold_left_<lift_<F>, lift_<C>>>::template
                    f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In,
                                                                                    T0>,
                                                                                    T1>,
                                                                                T2>,
                                                                                T3>,
                                                                            T4>,
                                                                            T5>,
                                                                        T6>,
                                                                        T7>,
                                                                    T8>,
                                                                    T9>,
                                                                T10>,
                                                                T11>,
                                                            T12>,
                                                            T13>,
                                                        T14>,
                                                        T15>,
                                                    T16>,
                                                    T17>,
                                                T18>,
                                                T19>,
                                            T20>,
                                            T21>,
                                        T22>,
                                        T23>,
                                    T24>,
                                    T25>,
                                T26>,
                                T27>,
                            T28>,
                            T29>,
                        T30>,
                        Ts...>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<33, fold_left_<lift_<F>, lift_<C>>>
        : dispatch<32, fold_left_<lift_<F>, lift_<C>>> {};
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<64, fold_left_<lift_<F>, lift_<C>>> {
        template<typename In,  typename T0,  typename T1,  typename T2,  typename T3,
                typename T4,  typename T5,  typename T6,  typename T7,  typename T8,
                typename T9,  typename T10, typename T11, typename T12, typename T13,
                typename T14, typename T15, typename T16, typename T17, typename T18,
                typename T19, typename T20, typename T21, typename T22, typename T23,
                typename T24, typename T25, typename T26, typename T27, typename T28,
                typename T29, typename T30, typename T31, typename T32, typename T33,
                typename T34, typename T35, typename T36, typename T37, typename T38,
                typename T39, typename T40, typename T41, typename T42, typename T43,
                typename T44, typename T45, typename T46, typename T47, typename T48,
                typename T49, typename T50, typename T51, typename T52, typename T53,
                typename T54, typename T55, typename T56, typename T57, typename T58,
                typename T59, typename T60, typename T61, typename T62, typename T63,
                typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                fold_left_<lift_<F>, lift_<C>>>::
        template f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In,
                                                                                                                                                    T0>,
                                                                                                                                                T1>,
                                                                                                                                                T2>,
                                                                                                                                            T3>,
                                                                                                                                            T4>,
                                                                                                                                        T5>,
                                                                                                                                        T6>,
                                                                                                                                    T7>,
                                                                                                                                    T8>,
                                                                                                                                T9>,
                                                                                                                                T10>,
                                                                                                                            T11>,
                                                                                                                            T12>,
                                                                                                                        T13>,
                                                                                                                        T14>,
                                                                                                                    T15>,
                                                                                                                    T16>,
                                                                                                                T17>,
                                                                                                                T18>,
                                                                                                            T19>,
                                                                                                            T20>,
                                                                                                        T21>,
                                                                                                        T22>,
                                                                                                    T23>,
                                                                                                    T24>,
                                                                                                T25>,
                                                                                                T26>,
                                                                                            T27>,
                                                                                            T28>,
                                                                                        T29>,
                                                                                        T30>,
                                                                                    T31>,
                                                                                    T32>,
                                                                                T33>,
                                                                                T34>,
                                                                            T35>,
                                                                            T36>,
                                                                        T37>,
                                                                        T38>,
                                                                    T39>,
                                                                    T40>,
                                                                T41>,
                                                                T42>,
                                                            T43>,
                                                            T44>,
                                                        T45>,
                                                        T46>,
                                                    T47>,
                                                    T48>,
                                                T49>,
                                                T50>,
                                            T51>,
                                            T52>,
                                        T53>,
                                        T54>,
                                    T55>,
                                    T56>,
                                T57>,
                                T58>,
                            T59>,
                            T60>,
                        T61>,
                        T62>,
                    T63>,
                    Ts...>;
    };
    template <std::size_t N, template <typename...> class F, template <typename...> class C>
    struct dispatch<N, fold_left_<lift_<F>, lift_<C>>>
        : dispatch<64, fold_left_<lift_<F>, lift_<C>>> {};
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, fold_left_<F, C>>
        : dispatch<N, fold_left_<lift_<dispatch<2, F>::template f>,
                                    lift_<dispatch<1, C>::template f>>> {};
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, fold_left_<lift_<F>, C>>
        : dispatch<N, fold_left_<lift_<F>, lift_<dispatch<1, C>::template f>>> {};
    template <std::size_t N, typename F, template <typename...> class C>
    struct dispatch<N, fold_left_<F, lift_<C>>>
        : dispatch<N, fold_left_<lift_<dispatch<2, F>::template f>, lift_<C>>> {};

} // namespace impl

// fold_right_ : folds right over a list using a binary predicate
// fold right considers the last element in the input pack the initial state, use
// push_back to add initial state if needed
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct fold_right_ {};
namespace impl { // fold_right_
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<0, fold_right_<lift_<F>, lift_<C>>> {
        template <typename...>
        using f = nothing_;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<1, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T>
        using f = C<T>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<2, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename In>
        using f = C<F<In, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<3, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename In>
        using f = C<F<F<In, T1>, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<4, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename T2, typename In>
        using f = C<F<F<F<In, T2>, T1>, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<5, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename T2, typename T3, typename In>
        using f = C<F<F<F<F<In, T3>, T2>, T1>, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<6, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename In>
        using f = C<F<F<F<F<F<In, T4>, T3>, T2>, T1>, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<7, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename In>
        using f = C<F<F<F<F<F<F<In, T5>, T4>, T3>, T2>, T1>, T0>>;
    };
    template <template <typename...> class F, template <typename...> class C>
    struct dispatch<8, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename In>
        using f = C<F<F<F<F<F<F<F<In, T6>, T5>, T4>, T3>, T2>, T1>, T0>>;
    };
    template <std::size_t N, template <typename...> class F, template <typename...> class C>
    struct dispatch<N, fold_right_<lift_<F>, lift_<C>>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename... Ts>
        using f = C<F<F<F<F<F<F<F<F<F<typename dispatch<find_dispatch(sizeof...(Ts)),
                                            fold_right_<lift_<F>, identity_>>::template f<Ts...>,
                                    T8>,
                                T7>,
                                T6>,
                            T5>,
                            T4>,
                        T3>,
                        T2>,
                    T1>,
                    T0>>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, fold_right_<F, C>>
        : dispatch<N, fold_right_<lift_<dispatch<2, F>::template f>,
                                    lift_<dispatch<1, C>::template f>>> {};
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, fold_right_<lift_<F>, C>>
        : dispatch<N, fold_right_<lift_<F>, lift_<dispatch<1, C>::template f>>> {};
    template <std::size_t N, typename F, template <typename...> class C>
    struct dispatch<N, fold_right_<F, lift_<C>>>
        : dispatch<N, fold_right_<lift_<dispatch<2, F>::template f>, lift_<C>>> {};
} // namespace impl

BOOST_TMP_EXPORT template <typename C = listify_>
struct join_ {};

BOOST_TMP_EXPORT template<typename C = listify_>
struct join_seq_ {};

template<std::size_t... Is>
using IndexSeq = std::index_sequence<Is...>;

// template<int... Is>
// using IntSeq = std::integer_sequence<Is...>;

BOOST_TMP_EXPORT template<typename... Ts> requires(std::same_as<Ts, std::size_t> && ...)
using into_sequence = IndexSeq<Ts::value...>;

namespace impl {
    template <template <typename...> class C, typename...>
    struct joiner;
    template <template <typename...> class C,
                typename... T0s, typename... T1s, typename... T2s, typename... T3s,
                typename... T4s, typename... T5s, typename... T6s, typename... T7s>
    struct joiner<C, list_<T0s...>, list_<T1s...>, list_<T2s...>, list_<T3s...>,
                        list_<T4s...>, list_<T5s...>, list_<T6s...>, list_<T7s...>> {
        template <typename... Vs>
        using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., Vs...>;
    };
    template<template <typename...> class C,
            typename... T0s,  typename... T1s,  typename... T2s,  typename... T3s,
            typename... T4s,  typename... T5s,  typename... T6s,  typename... T7s,
            typename... T8s,  typename... T9s,  typename... T10s, typename... T11s,
            typename... T12s, typename... T13s, typename... T14s, typename... T15s,
            typename... T16s, typename... T17s, typename... T18s, typename... T19s,
            typename... T20s, typename... T21s, typename... T22s, typename... T23s,
            typename... T24s, typename... T25s, typename... T26s, typename... T27s,
            typename... T28s, typename... T29s, typename... T30s, typename... T31s>
    struct joiner<C, list_<T0s...>,  list_<T1s...>,  list_<T2s...>,  list_<T3s...>,
                    list_<T4s...>,  list_<T5s...>,  list_<T6s...>,  list_<T7s...>,
                    list_<T8s...>,  list_<T9s...>,  list_<T10s...>, list_<T11s...>,
                    list_<T12s...>, list_<T13s...>, list_<T14s...>, list_<T15s...>,
                    list_<T16s...>, list_<T17s...>, list_<T18s...>, list_<T19s...>,
                    list_<T20s...>, list_<T21s...>, list_<T22s...>, list_<T23s...>,
                    list_<T24s...>, list_<T25s...>, list_<T26s...>, list_<T27s...>,
                    list_<T28s...>, list_<T29s...>, list_<T30s...>, list_<T31s...>> {
        template <typename... Vs>
        using f = C<T0s...,  T1s...,  T2s...,  T3s...,  T4s...,  T5s...,  T6s...,  T7s...,
                    T8s...,  T9s...,  T10s..., T11s..., T12s..., T13s..., T14s..., T15s...,
                    T16s..., T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s...,
                    T24s..., T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., Vs...>;
    };
    template <std::size_t N>
    struct join_loop;
    template <>
    struct join_loop<1> {
        template <template <typename...> class C,
                typename T0  = list_<>, typename T1  = list_<>, typename T2  = list_<>,
                typename T3  = list_<>, typename T4  = list_<>, typename T5  = list_<>,
                typename T6  = list_<>, typename T7  = list_<>, typename T8  = list_<>,
                typename T9  = list_<>, typename T10 = list_<>, typename T11 = list_<>,
                typename T12 = list_<>, typename T13 = list_<>, typename T14 = list_<>,
                typename T15 = list_<>, typename T16 = list_<>, typename T17 = list_<>,
                typename T18 = list_<>, typename T19 = list_<>, typename T20 = list_<>,
                typename T21 = list_<>, typename T22 = list_<>, typename T23 = list_<>,
                typename T24 = list_<>, typename T25 = list_<>, typename T26 = list_<>,
                typename T27 = list_<>, typename T28 = list_<>, typename T29 = list_<>,
                typename T30 = list_<>, typename T31 = list_<>, typename... Ts>
        using f = join_loop<(sizeof...(Ts) > 8)>::template f<
                joiner<C, T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12, T13,
                        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
                        T28, T29, T30, T31>::template f, Ts...>;
    };
    template <>
    struct join_loop<0> {
        template <template <typename...> class C,
                typename T0 = list_<>, typename T1 = list_<>, typename T2 = list_<>,
                typename T3 = list_<>, typename T4 = list_<>, typename T5 = list_<>,
                typename T6 = list_<>, typename T7 = list_<>, typename T8 = list_<>>
        using f = joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
    };
    template <std::size_t N, template <typename...> class C>
    struct dispatch<N, join_<lift_<C>>> {
        template <typename... Ts>
        using f = join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, join_<C>> {
        template <typename... Ts>
        using f = join_loop<(
                sizeof...(Ts) > 8)>::template f<dispatch_unknown<C>::template f, Ts...>;
    };

    // Sequence joining metaclosures
    template <template <typename...> class C, typename...>
    struct seq_joiner;
    template <template <typename...> class C, std::size_t... T0s, std::size_t... T1s,
                std::size_t... T2s, std::size_t... T3s, std::size_t... T4s, std::size_t... T5s,
                std::size_t... T6s, std::size_t... T7s>
    struct seq_joiner<C, IndexSeq<T0s...>, IndexSeq<T1s...>, IndexSeq<T2s...>, IndexSeq<T3s...>,
                    IndexSeq<T4s...>, IndexSeq<T5s...>, IndexSeq<T6s...>, IndexSeq<T7s...>> {
        template <typename... Vs>
        using f = C<sizet_<T0s>..., sizet_<T1s>..., sizet_<T2s>..., sizet_<T3s>..., sizet_<T4s>..., sizet_<T5s>..., sizet_<T6s>..., sizet_<T7s>..., Vs...>;
    };
    template <template <typename...> class C,
            std::size_t... T0s,  std::size_t... T1s,  std::size_t... T2s,  std::size_t... T3s,
            std::size_t... T4s,  std::size_t... T5s,  std::size_t... T6s,  std::size_t... T7s,
            std::size_t... T8s,  std::size_t... T9s,  std::size_t... T10s, std::size_t... T11s,
            std::size_t... T12s, std::size_t... T13s, std::size_t... T14s, std::size_t... T15s,
            std::size_t... T16s, std::size_t... T17s, std::size_t... T18s, std::size_t... T19s,
            std::size_t... T20s, std::size_t... T21s, std::size_t... T22s, std::size_t... T23s,
            std::size_t... T24s, std::size_t... T25s, std::size_t... T26s, std::size_t... T27s,
            std::size_t... T28s, std::size_t... T29s, std::size_t... T30s, std::size_t... T31s>
    struct seq_joiner<C, IndexSeq<T0s...>,  IndexSeq<T1s...>,  IndexSeq<T2s...>,  IndexSeq<T3s...>,
                        IndexSeq<T4s...>,  IndexSeq<T5s...>,  IndexSeq<T6s...>,  IndexSeq<T7s...>,
                        IndexSeq<T8s...>,  IndexSeq<T9s...>,  IndexSeq<T10s...>, IndexSeq<T11s...>,
                        IndexSeq<T12s...>, IndexSeq<T13s...>, IndexSeq<T14s...>, IndexSeq<T15s...>,
                        IndexSeq<T16s...>, IndexSeq<T17s...>, IndexSeq<T18s...>, IndexSeq<T19s...>,
                        IndexSeq<T20s...>, IndexSeq<T21s...>, IndexSeq<T22s...>, IndexSeq<T23s...>,
                        IndexSeq<T24s...>, IndexSeq<T25s...>, IndexSeq<T26s...>, IndexSeq<T27s...>,
                        IndexSeq<T28s...>, IndexSeq<T29s...>, IndexSeq<T30s...>, IndexSeq<T31s...>> {
        template <typename... Vs>
        using f = C<sizet_<T0s>...,  sizet_<T1s>...,  sizet_<T2s>...,  sizet_<T3s>...,
                    sizet_<T4s>...,  sizet_<T5s>...,  sizet_<T6s>...,  sizet_<T7s>...,
                    sizet_<T8s>...,  sizet_<T9s>...,  sizet_<T10s>..., sizet_<T11s>...,
                    sizet_<T12s>..., sizet_<T13s>..., sizet_<T14s>..., sizet_<T15s>...,
                    sizet_<T16s>..., sizet_<T17s>..., sizet_<T18s>..., sizet_<T19s>...,
                    sizet_<T20s>..., sizet_<T21s>..., sizet_<T22s>..., sizet_<T23s>...,
                    sizet_<T24s>..., sizet_<T25s>..., sizet_<T26s>..., sizet_<T27s>...,
                    sizet_<T28s>..., sizet_<T29s>..., sizet_<T30s>..., sizet_<T31s>..., Vs...>;
    };
    template <std::size_t N>
    struct seq_join_loop;
    template <>
    struct seq_join_loop<1> {
        template <template <typename...> class C,
                typename T0  = IndexSeq<>, typename T1  = IndexSeq<>, typename T2  = IndexSeq<>,
                typename T3  = IndexSeq<>, typename T4  = IndexSeq<>, typename T5  = IndexSeq<>,
                typename T6  = IndexSeq<>, typename T7  = IndexSeq<>, typename T8  = IndexSeq<>,
                typename T9  = IndexSeq<>, typename T10 = IndexSeq<>, typename T11 = IndexSeq<>,
                typename T12 = IndexSeq<>, typename T13 = IndexSeq<>, typename T14 = IndexSeq<>,
                typename T15 = IndexSeq<>, typename T16 = IndexSeq<>, typename T17 = IndexSeq<>,
                typename T18 = IndexSeq<>, typename T19 = IndexSeq<>, typename T20 = IndexSeq<>,
                typename T21 = IndexSeq<>, typename T22 = IndexSeq<>, typename T23 = IndexSeq<>,
                typename T24 = IndexSeq<>, typename T25 = IndexSeq<>, typename T26 = IndexSeq<>,
                typename T27 = IndexSeq<>, typename T28 = IndexSeq<>, typename T29 = IndexSeq<>,
                typename T30 = IndexSeq<>, typename T31 = IndexSeq<>, typename... Ts>
        using f = seq_join_loop<(sizeof...(Ts) > 8)>::template f<
                seq_joiner<C, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
                            T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
                            T28, T29, T30, T31>::template f, Ts...>;
    };
    template <>
    struct seq_join_loop<0> {
        template <template <typename...> class C,
                typename T0 = IndexSeq<>, typename T1 = IndexSeq<>, typename T2 = IndexSeq<>,
                typename T3 = IndexSeq<>, typename T4 = IndexSeq<>, typename T5 = IndexSeq<>,
                typename T6 = IndexSeq<>, typename T7 = IndexSeq<>, typename T8 = IndexSeq<>>
        using f = seq_joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
    };
    template <std::size_t N, template <typename...> class C>
    struct dispatch<N, join_seq_<lift_<C>>> {
        template <typename... Ts>
        using f = seq_join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, join_seq_<C>> {
        template <typename... Ts>
        using f = seq_join_loop<(sizeof...(Ts) > 8)>::template
                    f<dispatch_unknown<C>::template f, Ts...>;
    };
} // namespace impl

// reverse_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, ..., TN
// apply  - (reverse element order of parameter pack)
// result -  TN, ..., T1, T0
// Empty return type: list_<>
BOOST_TMP_EXPORT template <typename C = listify_>
struct reverse_ {};
namespace impl { // reverse_
    template <typename C, typename... Ts>
    struct reverse_impl {
        template <typename... Us>
        using f = dispatch<
            find_dispatch(sizeof...(Ts) + sizeof...(Us)), C>::template f<Ts..., Us...>;
    };
    template <typename C>
    struct dispatch<0, reverse_<C>> {
        template <typename...>
        using f = dispatch<0, C>::template f<>;
    };
    template <typename C>
    struct dispatch<1, reverse_<C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<T>;
    };
    template <typename C>
    struct dispatch<2, reverse_<C>> {
        template <typename T0, typename T1>
        using f = dispatch<2, C>::template f<T1, T0>;
    };
    template <typename C>
    struct dispatch<3, reverse_<C>> {
        template <typename T0, typename T1, typename T2>
        using f = dispatch<3, C>::template f<T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<4, reverse_<C>> {
        template <typename T0, typename T1, typename T2, typename T3>
        using f = dispatch<4, C>::template f<T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<5, reverse_<C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4>
        using f = dispatch<5, C>::template f<T4, T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<6, reverse_<C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5>
        using f = dispatch<6, C>::template f<T5, T4, T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<7, reverse_<C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6>
        using f = dispatch<7, C>::template f<T6, T5, T4, T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<8, reverse_<C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7>
        using f = dispatch<8, C>::template f<T7, T6, T5, T4, T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<9, reverse_<C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                            reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
                                template f<T7, T6, T5, T4, T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<16, reverse_<C>> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15>
        using f = dispatch<16, C>::template f<T15, T14, T13, T12, T11, T10, T9, T8,
                                                T7,  T6,  T5,  T4,  T3,  T2,  T1, T0>;
    };
    template <typename C>
    struct dispatch<17, reverse_<C>> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                                    reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
                template f<T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1, T0>;
    };
    template <typename C>
    struct dispatch<32, reverse_<C>> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31>
        using f = dispatch<32, C>::template f<T31, T30, T29, T28, T27, T26, T25, T24,
                                            T23, T22, T21, T20, T19, T18, T17, T16,
                                            T15, T14, T13, T12, T11, T10, T9,  T8,
                                            T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
    };
    template <typename C>
    struct dispatch<33, reverse_<C>> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), reverse_<lift_<reverse_impl>>>::template
                    f<Ts..., C>::template f<T31, T30, T29, T28, T27, T26, T25, T24,
                                            T23, T22, T21, T20, T19, T18, T17, T16,
                                            T15, T14, T13, T12, T11, T10, T9,  T8,
                                            T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
    };
    template <typename C>
    struct dispatch<64, reverse_<C>> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename T32, typename T33, typename T34,
                typename T35, typename T36, typename T37, typename T38, typename T39,
                typename T40, typename T41, typename T42, typename T43, typename T44,
                typename T45, typename T46, typename T47, typename T48, typename T49,
                typename T50, typename T51, typename T52, typename T53, typename T54,
                typename T55, typename T56, typename T57, typename T58, typename T59,
                typename T60, typename T61, typename T62, typename T63>
        using f = dispatch<16, C>::template f<T63, T62, T61, T60, T59, T58, T57, T56,
                                            T55, T54, T53, T52, T51, T50, T49, T48,
                                            T47, T46, T45, T44, T43, T42, T41, T40,
                                            T39, T38, T37, T36, T35, T34, T33, T32,
                                            T31, T30, T29, T28, T27, T26, T25, T24,
                                            T23, T22, T21, T20, T19, T18, T17, T16,
                                            T15, T14, T13, T12, T11, T10, T9,  T8,
                                            T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
    };
    template <typename C>
    struct dispatch<65, reverse_<C>> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename T32, typename T33, typename T34,
                typename T35, typename T36, typename T37, typename T38, typename T39,
                typename T40, typename T41, typename T42, typename T43, typename T44,
                typename T45, typename T46, typename T47, typename T48, typename T49,
                typename T50, typename T51, typename T52, typename T53, typename T54,
                typename T55, typename T56, typename T57, typename T58, typename T59,
                typename T60, typename T61, typename T62, typename T63, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                        reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::template
                        f<T63, T62, T61, T60, T59, T58, T57, T56, T55, T54, T53, T52, T51, T50,
                        T49, T48, T47, T46, T45, T44, T43, T42, T41, T40, T39, T38, T37, T36,
                        T35, T34, T33, T32, T31, T30, T29, T28, T27, T26, T25, T24, T23, T22,
                        T21, T20, T19, T18, T17, T16, T15, T14, T13, T12, T11, T10, T9,  T8,
                        T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, reverse_<C>> : dispatch<65, reverse_<C>> {};
} // namespace impl

// rotate_ :
// Input params: Parameter pack
// Closure params: N - Positive (for now) integer type
//                 C - Continuation; default listify_
// Functional description:
// input  - T0, T1, ..., TN
// apply  - (M rotations)
// result - T(M), T(M + 1), ..., T0, T1, ..., TN, ..., T(M - 1)
// Empty return type: list_<>
// FIXME: Add negative rotation.
// FIXME: If rotation count > element count; use modulo.
BOOST_TMP_EXPORT template <typename N = sizet_<0>, typename C = listify_>
struct rotate_ {};
namespace impl { // rotate_
    template <std::size_t, typename C>
    struct rotate_impl;
    template <typename C>
    struct rotate_impl<0, C> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
    };
    template <typename C>
    struct rotate_impl<1, C> {
        template <typename T, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template
                        f<Ts..., T>;
    };
    template <typename C>
    struct rotate_impl<2, C> {
        template <typename T0, typename T1, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 2), C>::template
                        f<Ts..., T0, T1>;
    };
    template <typename C>
    struct rotate_impl<3, C> {
        template <typename T0, typename T1, typename T2, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 3), C>::template
                        f<Ts..., T0, T1, T2>;
    };
    template <typename C>
    struct rotate_impl<4, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 4), C>::template
                        f<Ts..., T0, T1, T2, T3>;
    };
    template <typename C>
    struct rotate_impl<5, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 5), C>::template
                        f<Ts..., T0, T1, T2, T3, T4>;
    };
    template <typename C>
    struct rotate_impl<6, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 6), C>::template
                        f<Ts..., T0, T1, T2, T3, T4, T5>;
    };
    template <typename C>
    struct rotate_impl<7, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 7), C>::template
                        f<Ts..., T0, T1, T2, T3, T4, T5, T6>;
    };
    template <typename C>
    struct rotate_impl<8, C> {
        template<typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 8), C>::template
                        f<Ts..., T0, T1, T2, T3, T4, T5, T6, T7>;
    };
    template <typename C>
    struct rotate_impl<16, C> {
        template<typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 16), C>::template
                        f<Ts..., T0, T1, T2,  T3,  T4,  T5,  T6,  T7,
                                T8, T9, T10, T11, T12, T13, T14, T15>;
    };
    template <typename C>
    struct rotate_impl<32, C> {
        template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 32), C>::template
                        f<Ts..., T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,
                                T8,  T9,  T10, T11, T12, T13, T14, T15,
                                T16, T17, T18, T19, T20, T21, T22, T23,
                                T24, T25, T26, T27, T28, T29, T30, T31>;
    };
    template <typename C>
    struct rotate_impl<64, C> {
        template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename T32, typename T33, typename T34,
                typename T35, typename T36, typename T37, typename T38, typename T39,
                typename T40, typename T41, typename T42, typename T43, typename T44,
                typename T45, typename T46, typename T47, typename T48, typename T49,
                typename T50, typename T51, typename T52, typename T53, typename T54,
                typename T55, typename T56, typename T57, typename T58, typename T59,
                typename T60, typename T61, typename T62, typename T63, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 64), C>::template
                        f<Ts..., T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10,
                                T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                                T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32,
                                T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
                                T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
                                T55, T56, T57, T58, T59, T60, T61, T62, T63>;
    };
    template <typename P, typename C>
    struct dispatch<0, rotate_<P, C>> {
        template <typename...>
        using f = dispatch<0, C>::template f<>;
    };
    template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
    struct make_rotate
        : rotate_impl<step_selector(Step), rotate_<sizet_<(P - Step)>, C>> { /* not done */
    };
    template <std::size_t P, typename C>
    struct make_rotate<P, C, P> : rotate_impl<P, C> {};
    template <std::size_t N, typename P, typename C>
    struct dispatch<N, rotate_<P, C>> : make_rotate<P::value, C> {};
} // namespace impl

// size_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default identity_
// Functional description:
// input  - T0, T1, ..., TN (Ts...)
// apply  - (get number of elements in parameter pack)
// result - sizet_<sizeof...(Ts)>
// Empty return type: sizet_<0>
BOOST_TMP_EXPORT template <typename C = identity_>
struct size_ {};
namespace impl { // size_
    template <std::size_t N, typename C>
    struct dispatch<N, size_<C>> {
        template <typename... Ls>
        using f = dispatch<1, C>::template f<sizet_<sizeof...(Ls)>>;
    };
} // namespace impl

// swap_ : Swaps two variadic parameter pack values. Must be only two values.
BOOST_TMP_EXPORT template <typename C = listify_>
struct swap_ {};
namespace impl { // swap_
    template <typename C>
    struct dispatch<2, swap_<C>> {
        template <typename T, typename U>
        using f = dispatch<2, C>::template f<U, T>;
    };
    template<std::size_t N, typename C> requires(N == 2)
    struct dispatch<N, swap_<C>> {
        template<typename...>
        using f = nothing_;
    };
} // namespace impl

// transform_ : 
BOOST_TMP_EXPORT template <typename F = identity_, typename C = listify_>
struct transform_ {};
namespace impl { // transform_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, transform_<F, C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<
                        typename dispatch<1, F>::template f<Ts>...>;
    };
    template <std::size_t N, template <typename...> class F, typename FC, typename C>
    struct dispatch<N, transform_<lift_<F, FC>, C>> {
    template <typename... Ts>
    using f = dispatch<(N + (N > sizeof...(Ts))), C>::template f<F<Ts>...>;
};
} // namespace impl

// drop_ : Remove (N) values from the front of the input VPP.
// Input params: Parameter pack
// Closure params: N - Positive integer type
//                 C - Continuation; default listify_
// Functional description:
// input  - T0, T1, ..., T(M), T(M + 1), ..., TN
// apply  - (drop M values)
// result - T(M), T(M + 1), ..., TN
// Empty return type: list_<>
BOOST_TMP_EXPORT template <Sizable N = sizet_<0>, typename C = listify_>
struct drop_ {};
namespace impl { // drop_
    template <std::size_t, typename C>
    struct drop_impl;
    // TODO: Is this correct behavior for dropping nothing?
    template <typename C>
    struct drop_impl<0, C> {
        template <typename... Ts>
        using f = call_<C, Ts...>;
    };
    template <typename C>
    struct drop_impl<1, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<2, C> {
        template <typename T0, typename T1, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<3, C> {
        template <typename T0, typename T1, typename T2, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<4, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<5, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<6, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<7, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<8, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<16, C> {
        template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<32, C> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <typename C>
    struct drop_impl<64, C> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16, typename T17, typename T18, typename T19,
                typename T20, typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28, typename T29,
                typename T30, typename T31, typename T32, typename T33, typename T34,
                typename T35, typename T36, typename T37, typename T38, typename T39,
                typename T40, typename T41, typename T42, typename T43, typename T44,
                typename T45, typename T46, typename T47, typename T48, typename T49,
                typename T50, typename T51, typename T52, typename T53, typename T54,
                typename T55, typename T56, typename T57, typename T58, typename T59,
                typename T60, typename T61, typename T62, typename T63, typename... Ts>
        using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
    };
    template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
    struct make_drop : drop_impl<Step, drop_<sizet_<(P - Step)>, C>> { /* not done */
    };
    template <std::size_t P, typename C>
    struct make_drop<P, C, P> : drop_impl<P, C> {};
    template <std::size_t N, typename P, typename C>
    struct dispatch<N, drop_<P, C>> : make_drop<P::value, C> {};
} // namespace impl

// drop_last_ :
BOOST_TMP_EXPORT template<Sizable N = sizet_<0>, typename C = listify_>
struct drop_last_ {};
namespace impl { // drop_last_
    template<std::size_t N, typename DropN, typename C>
    struct dispatch<N, drop_last_<DropN, C>> : dispatch<N, reverse_<drop_<DropN, reverse_<C>>>> {};
} // namespace impl

// push_back_ :
BOOST_TMP_EXPORT template <typename T, typename C = listify_>
struct push_back_ {};
namespace impl { // push_back_
    template <std::size_t N, typename T, typename C>
    struct dispatch<N, push_back_<T, C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
    };
} // namespace impl

// pop_front_ :
BOOST_TMP_EXPORT template <typename C = listify_>
struct pop_front_ {};
namespace impl { // pop_front_
    template <std::size_t N, typename C>
    struct dispatch<N, pop_front_<C>> {
        template <typename T, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
    };
    // TODO: Should this be kept? This differs from the behavior of popping
    // the front off of an empty list (which results in an empty list).
    // This, however, will return a list_<nothing_>
    template <typename C>
    struct dispatch<0, pop_front_<C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<nothing_>;
};
} // namespace impl

// push_front_ :
BOOST_TMP_EXPORT template <typename T, typename C = listify_>
struct push_front_ {};
namespace impl { // push_front_
    template <std::size_t N, typename T, typename C>
    struct dispatch<N, push_front_<T, C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<T, Ts...>;
    };
} // namespace impl

// pop_back_ :
BOOST_TMP_EXPORT template <typename C = listify_>
struct pop_back_ {};
namespace impl { // pop_back_
    template<std::size_t N, typename C>
    struct dispatch<N, pop_back_<C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), rotate_<sizet_<sizeof...(Ts) - 1>, pop_front_<
                        rotate_<sizet_<(sizeof...(Ts) - 1)>, C>>>>::template f<Ts...>;
    };
    template <typename C>
    struct dispatch<0, pop_back_<C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<nothing_>;
    };
} // namespace impl

BOOST_TMP_EXPORT template<Sizable I, typename C = identity_>
struct index_ {};
BOOST_TMP_EXPORT template<Sizable I, typename C = identity_>
using unpack_index_ = unpack_<index_<I, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using front_ = index_<sizet_<0>, C>;

BOOST_TMP_EXPORT template<typename C = identity_>
using i0_ = index_<sizet_<0>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i1_ = index_<sizet_<1>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i2_ = index_<sizet_<2>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i3_ = index_<sizet_<3>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i4_ = index_<sizet_<4>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i5_ = index_<sizet_<5>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i6_ = index_<sizet_<6>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using i7_ = index_<sizet_<7>, C>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui0_ = unpack_<index_<sizet_<0>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui1_ = unpack_<index_<sizet_<1>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui2_ = unpack_<index_<sizet_<2>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui3_ = unpack_<index_<sizet_<3>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui4_ = unpack_<index_<sizet_<4>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui5_ = unpack_<index_<sizet_<5>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui6_ = unpack_<index_<sizet_<6>, C>>;
BOOST_TMP_EXPORT template<typename C = identity_>
using ui7_ = unpack_<index_<sizet_<7>, C>>;
namespace impl { // index_
    template <std::size_t N, typename I, typename C>
    struct dispatch<N, index_<I, C>> : dispatch<N, drop_<I, front_<C>>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, index_<nothing_, C>> {
        template <typename... Ts>
        using f = nothing_;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<0>, C>> {
        template <typename T0, typename... Ts>
        using f = dispatch<1, C>::template f<T0>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<1>, C>> {
        template <typename T0, typename T1, typename... Ts>
        using f = dispatch<1, C>::template f<T1>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<2>, C>> {
        template <typename T0, typename T1, typename T2, typename... Ts>
        using f = dispatch<1, C>::template f<T2>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<3>, C>> {
        template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
        using f = dispatch<1, C>::template f<T3>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<4>, C>> {
        template<typename T0, typename T1, typename T2, typename T3,
                    typename T4, typename... Ts>
        using f = dispatch<1, C>::template f<T4>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<5>, C>> {
        template<typename T0, typename T1, typename T2, typename T3,
                    typename T4, typename T5, typename... Ts>
        using f = dispatch<1, C>::template f<T5>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<6>, C>> {
        template<typename T0, typename T1, typename T2, typename T3,
                    typename T4, typename T5, typename T6, typename... Ts>
        using f = dispatch<1, C>::template f<T6>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_<sizet_<7>, C>> {
    template <typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename T7, typename... Ts>
    using f = dispatch<1, C>::template f<T7>;
};
} // namespace impl

// erase_ : Given a VPP, remove the nth value in the pack.
// Reduces the size of the list by 1.
// Input params: Parameter pack
// Closure params: N - Positive integer type of index of element to remove
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, ..., T(M - 1), TM, T(M + 1), ..., TN
// apply  -  (erase element at index M)
// result -  T0, T1, ..., T(M - 1), T(M + 1), ..., TN
// Empty return type: list_<>
BOOST_TMP_EXPORT template <Sizable N = sizet_<0>, typename C = listify_>
struct erase_ {};
namespace impl { // erase_
    template <std::size_t N, typename I, typename C>
    struct dispatch<N, erase_<I, C>> {
        template <typename... Ts>
        using f = dispatch<N,
            rotate_<I,
                pop_front_<rotate_<sizet_<(sizeof...(Ts) - I::value - 1)>, C>>>>::template f<Ts...>;
    };
    template <typename I, typename C>
    struct dispatch<0, erase_<I, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<nothing_>;
    };
} // namespace impl

// insert_ :
BOOST_TMP_EXPORT template <Sizable N, typename V, typename C = listify_>
struct insert_ {};
namespace impl { // insert_
    template <std::size_t N, typename I, typename V, typename C>
    struct dispatch<N, insert_<I, V, C>> {
        template <typename... Ts>
        using f = dispatch<N, rotate_<I, push_front_<V, rotate_<sizet_<(sizeof...(Ts) - I::value + 1)>,
                                                        C>>>>::template f<Ts...>;
    };
    template <typename I, typename V, typename C>
    struct dispatch<0, insert_<I, V, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<V>;
    };
} // namespace impl

// make_sequence_ :
BOOST_TMP_EXPORT template <typename F = identity_, typename C = listify_>
struct make_sequence_ {};
namespace impl { // make_sequence_
    consteval std::size_t next_number(std::size_t current, std::size_t end) {
        return ((end - 2 * current) < 2) ?
                        end :
                        next_number(current,
                                    end / 2); // note that std::size_t / 2 always rounds down
    }
    consteval std::size_t next_state(std::size_t current, std::size_t end) {
        return ((end - current) < 2) ? end - current :
                                        (2 + (next_number(current, end) - 2 * current));
    }
    template <std::size_t State>
    struct make_seq_impl;
    template <>
    struct make_seq_impl<0> { // done
        template <std::size_t End, std::size_t... Is>
        using f = list_<sizet_<Is>...>;
    };
    template <>
    struct make_seq_impl<1> { // done +1
        template <std::size_t End, std::size_t... Is>
        using f = list_<sizet_<Is>..., sizet_<End - 1>>;
    };
    template <>
    struct make_seq_impl<2> { // double
        template <std::size_t End, std::size_t... Is>
        using f = make_seq_impl<next_state(2 * sizeof...(Is), End)>::template 
                    f<End, Is..., (Is + sizeof...(Is))...>;
    };
    template <>
    struct make_seq_impl<3> { // double +1
        template <std::size_t End, std::size_t... Is>
        using f = make_seq_impl<next_state(2 * sizeof...(Is) + 1, End)>::template f<
                        End, Is..., (Is + sizeof...(Is))..., (2 * sizeof...(Is))>;
    };
    template <typename F, typename C>
    struct dispatch<1, make_sequence_<F, C>> {
        template <typename N>
        using f = dispatch<1, unpack_<transform_<F, C>>>::template f<
                typename make_seq_impl<next_state(0, N::value)>::template f<N::value>>;
    };
    template <std::size_t N>
    using make_index_for_ = make_seq_impl<next_state(0, N)>::template f<N>;
} // namespace impl

// TODO: Benchmark alternate implemenation.
// template<typename... Vs>
// struct index_impl;
// template<std::size_t... Vs>
// struct index_impl<std::index_sequence<Vs...>> {
//     using f = list_<sizet_<Vs>...>;
// };
// template <typename F, typename C>
// struct dispatch<1, make_sequence_<F, C>> {
//     template <typename N>
//     using f = dispatch<1, unpack_<transform_<F, C>>>::template f<typename index_impl<std::make_index_sequence<N::value>>::template f>;
// };

// repeat_sequence_ :
BOOST_TMP_EXPORT template<Sizable N = sizet_<0>, typename C = listify_>
struct repeat_sequence_{};
namespace impl { // repeat_sequence_
    template <std::size_t, typename C>
    struct repeat_seq_impl;
    template <typename C>
    struct repeat_seq_impl<0, C> {
        template <typename...>
        using f = dispatch<0, C>::template f<>;
    };
    template <typename C>
    struct repeat_seq_impl<1, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 1, C>::template f<T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<2, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 2, C>::template f<T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<3, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 3, C>::template f<T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<4, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 4, C>::template f<T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<5, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 5, C>::template f<T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<6, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 6, C>::template f<T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<7, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 7, C>::template f<T, T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<8, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 8, C>::template f<T, T, T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<16, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 16, C>::template f<T, T, T, T, T, T, T, T,
                                                            T, T, T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<32, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 32, C>::template f<T, T, T, T, T, T, T, T,
                                                            T, T, T, T, T, T, T, T,
                                                            T, T, T, T, T, T, T, T,
                                                            T, T, T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<64, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 64, C>::template f<
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T, Ts...>;
    };
    template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
    struct make_repeat : repeat_seq_impl<Step, repeat_sequence_<sizet_<(P - Step) + 1>, C>> {};
    template <std::size_t P, typename C>
    struct make_repeat<P, C, P> : repeat_seq_impl<P, C> {};
    template <std::size_t N, typename P, typename C>
    struct dispatch<N, repeat_sequence_<P, C>> : make_repeat<P::value, C> {};
} // namespace impl

// is_ : 
BOOST_TMP_EXPORT template <typename P, typename C = identity_>
struct is_ {};
namespace impl { // is_
    template <typename P, typename C>
    struct dispatch<1, is_<P, C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<bool_<std::is_same_v<P, T>>>;
    };
} // namespace impl

// not_ : 
BOOST_TMP_EXPORT template <typename C = identity_>
struct not_ {};
namespace impl { // not_
    template <typename C>
    struct dispatch<1, not_<C>> {
        template <Boolable T>
        using f = dispatch<1, C>::template f<bool_<(!T::value)>>;
    };
} // namespace impl

// or_ : 
BOOST_TMP_EXPORT template <typename F = identity_, typename C = identity_>
struct or_ {};
namespace impl { // or_
    template <bool Short, template <typename...> class F>
    struct ory {
        template <typename T>
        using f                    = ory<F<T>::value, F>;
        static constexpr std::size_t value = -1;
    };
    template <template <typename...> class F>
    struct ory<true, F> {
        template <typename T>
        using f                    = ory;
        static constexpr std::size_t value = 1;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, or_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_, not_<identity_>>,
                        typename foldey<(select_foldey_loop(
                                sizeof...(Ts)))>::template f<ory<false, F>, 0, Ts...>>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<0, or_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, or_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_, not_<identity_>>,
                        typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
                                ory<false, dispatch<1, F>::template f>, 0, Ts...>>>;
    };
    template <typename F, typename C>
    struct dispatch<0, or_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
} // namespace impl

// and_ : 
BOOST_TMP_EXPORT template <typename F = identity_, typename C = identity_>
struct and_ {};
namespace impl { // and_
    template <bool Short, template <typename...> class F>
    struct andy {
        template <typename T>
        using f                    = andy<(!F<T>::value), F>;
        static constexpr std::size_t value = -1;
    };
    template <template <typename...> class F>
    struct andy<true, F> {
        template <typename T>
        using f                    = andy;
        static constexpr std::size_t value = 1;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, and_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_>, typename foldey<(select_foldey_loop(sizeof...(
                                                Ts)))>::template f<andy<false, F>, 0, Ts...>>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<0, and_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, and_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_>,
                        typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
                                andy<false, dispatch<1, F>::template f>, 0, Ts...>>>;
    };
    template <typename F, typename C>
    struct dispatch<0, and_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
} // namespace impl

// if_ : Given a predicate P, if true, return T, and if false, return F.
BOOST_TMP_EXPORT template <typename P, typename T, typename F = always_<nothing_>>
struct if_ {};
namespace impl { // if_
    template <bool B>
    struct if_impl;
    template <>
    struct if_impl<true> {
        template <typename T, typename U>
        using f = T;
    };
    template <>
    struct if_impl<false> {
        template <typename T, typename U>
        using f = U;
    };
    template <typename P, typename T, typename F>
    struct dispatch<1, if_<P, T, F>> {
        template <typename T0>
        using f = dispatch<1, typename if_impl<dispatch<1, P>::template
                        f<T0>::value>::template
                            f<T, F>>::template
                                f<T0>;
    };
    template <template <typename...> class P, typename T, typename F>
    struct dispatch<1, if_<lift_<P>, T, F>> {
        template <typename T0>
        using f = dispatch<1, typename if_impl<P<T0>::value>::template
                        f<T, F>>::template
                            f<T0>;
    };
    template <std::size_t N, typename P, typename T, typename F>
    struct dispatch<N, if_<P, T, F>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)),
                        typename if_impl<dispatch<find_dispatch(sizeof...(Ts)), P>::template
                            f<Ts...>::value>::template f<T, F>>::template f<Ts...>;
    };
    template <std::size_t N, template <typename...> class P, typename T, typename F>
    struct dispatch<N, if_<lift_<P>, T, F>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)),
                        typename if_impl<P<Ts...>::value>::template
                            f<T, F>>::template f<Ts...>;
    };
    template <template <typename...> class P, typename T, typename F>
    struct dispatch<2, if_<lift_<P>, T, F>> {
        template <typename T0, typename T1>
        using f = dispatch<2, typename if_impl<P<T0,T1>::value>::template
                        f<T, F>>::template f<T0, T1>;
    };
    template <template <typename...> class P>
    struct dispatch<1, if_<lift_<P>, listify_, always_<list_<>>>> {
        template <typename U>
        using f = if_impl<P<U>::value>::template f<list_<U>, list_<>>;
    };
} // namespace impl

// array_into_list_
template<auto Array, typename IS = decltype(std::make_index_sequence<Array.size()>())>
struct array_into_list_base;

template<auto Array, std::size_t... Is>
struct array_into_list_base<Array, std::index_sequence<Is...>> {
    using array_type = std::remove_extent_t<decltype(Array)>;
    using list_type = list_<int_<Array[Is]>...>;
};

BOOST_TMP_EXPORT template<auto Array>
using array_into_list_ = typename array_into_list_base<Array>::list_type;

// less_ : 
BOOST_TMP_EXPORT template <typename V = nothing_, typename C = identity_>
struct less_ {};
namespace impl { // less_
    template <typename C>
    struct dispatch<2, less_<C>> {
        template <typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
    };
    template <typename U, typename C>
    struct dispatch<1, less_<U, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
    };
} // namespace impl

// less_f_ : 
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct less_f_ {};
namespace impl { // less_f_
    template <template<typename...> typename F, typename C>
    struct dispatch<2, less_f_<lift_<F>, C>> {
        template<typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(F<T>::value < F<U>::value)>>;
    };
} // namespace impl

// less_eq_ : 
BOOST_TMP_EXPORT template <typename V = nothing_, typename C = identity_>
struct less_eq_ {};
namespace impl { // less_eq_
    template <typename C>
    struct dispatch<2, less_eq_<C>> {
        template <typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(T::value)<=(U::value)>>;
    };
    template <typename U, typename C>
    struct dispatch<1, less_eq_<U, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<(U::value)<=(T::value)>>;
    };
} // namespace impl

// greater_ : 
BOOST_TMP_EXPORT template <typename V = nothing_, typename C = identity_>
struct greater_ {};
namespace impl { // greater_
    template <typename C>
    struct dispatch<2, greater_<C>> {
        template <typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
    };
    template <typename U, typename C>
    struct dispatch<1, greater_<U, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
    };
} // namespace impl

// range_lo_hi_ : 
BOOST_TMP_EXPORT template <typename LV = nothing_, typename UV = nothing_, typename C = identity_>
struct range_lo_hi_ {};
namespace impl { // range_lo_hi_
    template <typename Lower, typename Upper, typename C>
    struct dispatch<1, range_lo_hi_<Lower, Upper, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<!((Lower::value < T::value) && (T::value < Upper::value))>>;
};

} // namespace impl

// all_of_ : Given a unary predicate, return true_ / false_ on whether all elements
// in a parameter pack satisfy that predicate. Shorting (uses and_).
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct all_of_ {};
namespace impl { // all_of_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, all_of_<F, C>> : dispatch<N, and_<F, C>> {};
} // namespace impl

// any_of_ : Given a unary predicate, return true_ / false_ on whether any elements
// in a VPP satisfy that predicate.
BOOST_TMP_EXPORT template <typename F = identity_, typename C = identity_>
struct any_of_ {};
namespace impl { // any_of_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, any_of_<F, C>> : dispatch<N, or_<F, C>> {};
} // namespace impl

// none_of_ : Given a predicate (F), return true_ / false_ if none
// of the elements in a VPP satisfy the predicate F.
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = identity_>
struct none_of_ {};
namespace impl { // none_of_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, none_of_<F, C>> : dispatch<N, and_<F, not_<C>>> {};
} // namespace impl

// flatten_ : 
BOOST_TMP_EXPORT template <typename C = listify_>
struct flatten_ {};
namespace impl { // flatten_
    template <typename C, typename... Ts>
    struct flatten_impl {
        using type = dispatch<0, join_<C>>::template f<Ts...>;
    };
    // Append to list function
    template <typename C, typename... T1s, typename X, typename... T2s>
    struct flatten_impl<C, list_<T1s...>, X, T2s...>
        : flatten_impl<C, list_<T1s..., X>, T2s...> {};
    // Remove from list function
    template <typename C, typename... T1s, template <typename...> class X, typename... T2s,
                typename... T3s>
    struct flatten_impl<C, list_<T1s...>, X<T2s...>, T3s...>
        : flatten_impl<C, list_<T1s...>, T2s..., T3s...> {};
    template <std::size_t N, typename C>
    struct dispatch<N, flatten_<C>> {
        template <typename... Ts>
        using f = flatten_impl<C, list_<>, Ts...>::type;
    };
} // namespace impl

BOOST_TMP_EXPORT template<typename LowerB, typename UpperB, typename C = listify_>
struct slice_ {};
namespace impl { // slice_
    template<std::size_t N, typename LowerB, typename UpperB, typename C>
    struct dispatch<N, slice_<LowerB, UpperB, C>> : dispatch<N, drop_<LowerB, drop_last_<UpperB, C>>> {};
} // namespace impl

// count_if_ : Given a predicate F, check the variadic parameter pack passed in and count
// each time that the predicate holds true. Returns n counts as sizet_<n>.
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = identity_>
struct count_if_ {};
namespace impl { // count_if_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, count_if_<F, C>>
        : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
                                    join_<size_<C>>>> {};
} // namespace impl

// Returns the index of the type that satisfies UnaryPredicate.
// find_if_ : 
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = identity_>
struct find_if_ {};
namespace impl { // find_if_
    template <bool Found, std::size_t At, template <typename...> class F>
    struct county {
        static constexpr auto value{std::numeric_limits<std::size_t>::max()};
        template <typename T>
        using f = county<F<T>::value, (At + 1), F>;
    };
    template <std::size_t At, template <typename...> class F>
    struct county<true, At, F> {
        template <typename T>
        using f                    = county;
        static constexpr std::size_t value = At;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, find_if_<F, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<
                        typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
                        county<false,
                                std::numeric_limits<std::size_t>::max(),
                                dispatch<1, F>::template f>, 0, Ts...>>;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, find_if_<lift_<F>, C>> {
            template <typename... Ts>
            using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                        sizeof...(Ts))>::template f<county<false,
                                                            std::numeric_limits<std::size_t>::max(),
                                                            F>, 0, Ts...>>;
    };
} // namespace impl

// find_if_not_ : 
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = identity_>
struct find_if_not_ {};
namespace impl { // find_if_not_
    template <bool Found, std::size_t At, template <typename...> class F>
    struct county_not {
        static constexpr auto value{std::numeric_limits<std::size_t>::max()};
        template <typename T>
        using f = county_not<F<T>::value, (At + 1), F>;
    };
    template <std::size_t At, template <typename...> class F>
    struct county_not<false, At, F> {
        template <typename T>
        using f                    = county_not;
        static constexpr std::size_t value = At;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, find_if_not_<F, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<
                        typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
                        county_not<true,
                                std::numeric_limits<std::size_t>::max(),
                                dispatch<1, F>::template f>, 0, Ts...>>;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, find_if_not_<lift_<F>, C>> {
            template <typename... Ts>
            using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                        sizeof...(Ts))>::template f<county_not<true,
                                                            std::numeric_limits<std::size_t>::max(),
                                                            F>, 0, Ts...>>;
    };
} // namespace impl

// remove_if_ : Given a predicate F, check the variadic parameter pack passed in
// and remove the value if the predicate holds true.
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = listify_>
struct remove_if_ {};
namespace impl { // remove_if_
    template<std::size_t N, typename F, typename C>
    struct dispatch<N, remove_if_<F, C>>
            : dispatch<N, filter_<if_<F, always_<false_>, always_<true_>>, C>> {};
} // namespace impl

// replace_if_ : Given a variadic parameter pack, replace every value that fulfills
// the predicate F with the value Input.
BOOST_TMP_EXPORT template <typename Input, typename UnaryPred, typename C = listify_>
struct replace_if_ {};
namespace impl { // replace_if_
    template <std::size_t N, typename Input, typename UnaryPred, typename C>
    struct dispatch<N, replace_if_<Input, UnaryPred, C>>
            : dispatch<N, transform_<if_<UnaryPred, always_<Input>, identity_>, C>> {};
} // namespace impl

// keys_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default listify_
// Functional description:
// input  - T0<t00, t01, ...>, T1<t10, t11, ...>, ..., TN<tN0, tN1, ...>
// apply  - (get 1st element from each element)
// result - list_<t00, t10, ..., tN0>
// Empty return type: list_<>
BOOST_TMP_EXPORT template<typename C = listify_>
struct keys_ {};
namespace impl { // keys_
    template <std::size_t N, typename C>
    struct dispatch<N, keys_<C>> : dispatch<N, transform_<ui0_<>, C>> {};
} // namespace impl

// values_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default listify_
// Functional description:
// input  -  T0<t00, t01, ...>, T1<t10, t11, ...>, ..., TN<tN0, tN1, ...>
// apply  -  (get 2nd element from each element)
// result -  list_<t01, t11, ..., tN1>
// Empty return type: list_<>
BOOST_TMP_EXPORT template<typename C = listify_>
struct values_ {};
namespace impl { // values_
    template <std::size_t N, typename C>
    struct dispatch<N, values_<C>> : dispatch<N, transform_<ui1_<>, C>> {};
} // namespace impl

// nth_values_ :
// Input params: Parameter pack
// Closure params: I - Positive integer type of the index to take from each element in pack.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0<t00, t01, ..., T0I, ...>, T1<t10, t11, ..., T1I, ...>, ..., TN<tN0, tN1, ..., TNI, ...>
// apply  -  (get Ith element from each element)
// result -  list_<T0I, T1I, ..., TNI>
// Empty return type: list_<>
BOOST_TMP_EXPORT template<Sizable I, typename C = listify_>
struct nth_values_ {};
namespace impl { // nth_values_
    template <std::size_t N, typename I, typename C>
    struct dispatch<N, nth_values_<I, C>> : dispatch<N, transform_<unpack_index_<I>, C>> {};
} // namespace impl

// clamp_ : Given a lower-bound type (L) and higher-bound type (H), and that both types
// are less than and greater than comparable, remove all types less than L and all types
// greater than H from a given VPP.
// The VPP values must also satisfy being less than and greater than comparable.
BOOST_TMP_EXPORT template <typename L, typename H, typename C = identity_>
struct clamp_ {};
namespace impl { // clamp_
    template <std::size_t N, typename L, typename H, typename C>
    struct dispatch<N, clamp_<L, H, C>>
        : dispatch<N, remove_if_<range_lo_hi_<L, H, C>>> {};
} // namespace impl

//  product_ : Given two lists, generates the Cartesian product of said lists (n x m tuples generated).
// 	using xl0 = list_<x<1>, x<2>, ..., x<n>>;
//	using xr0 = list_<x<1>, x<2>, ..., x<m>>;
//
//  using result = call_<product_<>, xl0, xr0>;
//  \text Will generate the Cartesian product of the lists xl0 and xr0, from xl0[1]-xl0[n]
//  and xr0[1]-xr0[m]: result = list_<list_<x<1>, x<1>>, list_<x<1>, x<2>>, ..., list_<x<1>,
//  x<n>>, ..., list_<x<n>, x<1>>, list_<x<n>, x<2>>, ..., list_<x<n>, x<m>>>
BOOST_TMP_EXPORT template <typename F = listify_, typename C = listify_>
struct product_ {};
namespace impl { // product_
    template <template <typename...> class F, typename T, typename... Ts>
    using product_helper_ = list_<F<T, Ts>...>;
    template <template <typename...> class F, typename C, typename T, typename U>
    struct product_unpacker {};
    template <template <typename...> class F, typename C, typename... Ts, typename... Us>
    struct product_unpacker<F, C, list_<Ts...>, list_<Us...>> {
        using type = dispatch<find_dispatch(sizeof...(Ts)),
                                    join_<C>>::template f<product_helper_<F, Ts, Us...>...>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<2, product_<lift_<F>, C>> {
        template <typename T, typename U>
        using f = product_unpacker<F, C, T, U>::type;
    };
    template <typename F, typename C>
    struct dispatch<2, product_<F, C>> : dispatch<2, product_<lift_<dispatch<2, F>::template f>, C>> {};
} // namespace impl

// sort_ :
BOOST_TMP_EXPORT template <typename F = less_<>, typename C = listify_>
struct sort_ {};
namespace impl { // sort_
    namespace btree {
        // The binary tree as a list.
        template <typename... Ts>
        struct blist {};

        // A node in the binary tree, connecting to other nodes (L)eft and (R)ight, and (E)dge
        template <typename L, typename E, typename R>
        struct bnode {};
        template <typename T>
        struct bun;
        template <bool, template <typename...> class F>
        struct bpush;
        template <template <typename...> class F>
        struct bpush<false, F> {
            template <typename T, typename L, typename E, typename R>
            using n = bnode<L, E, typename bun<R>::template f<F, T>>;
            template<typename T, typename LL, typename LE, typename LR,
                        typename E, typename RL, typename RE, typename RR>
            using nn = bpush<F<T, RE>::value, F>::template nn_0<T, LL, LE, LR, E, RL, RE, RR>;
            template <typename T, typename LL, typename LE, typename LR, typename E,
                        typename RL, typename RE, typename RR>
            using nn_0 = bnode<bnode<bnode<LL, LE, LR>, E, RL>, RE,
                                typename bun<RR>::template f<F, T>>;
            template <typename T, typename LL, typename LE, typename LR,
                        typename E, typename RL, typename RE, typename RR>
            using nn_1 = bnode<bnode<LL, LE, typename bun<LR>::template f<F, T>>, E,
                                bnode<RL, RE, RR>>;
            template <typename T, typename E>
            using l1 = blist<E, T>;
            template <typename T, typename E0, typename E1>
            using l2_0 = bpush<F<T, E1>::value, F>::template l2_1<T, E0, E1>;
            template <typename T, typename E0, typename E1>
            using l2_1 = bnode<blist<E0>, E1, blist<T>>;
        };
        template <template <typename...> class F>
        struct bpush<true, F> {
            template <typename T, typename L, typename E, typename R>
            using n = bnode<typename bun<L>::template f<F, T>, E, R>;
            template <typename T, typename LL, typename LE, typename LR,
                        typename E, typename RL, typename RE, typename RR>
            using nn = bpush<F<T, LE>::value, F>::template nn_1<T, LL, LE, LR, E, RL, RE, RR>;
            template <typename T, typename LL, typename LE, typename LR,
                        typename E, typename RL, typename RE, typename RR>
            using nn_0 = bnode<bnode<LL, LE, LR>, E,
                                bnode<typename bun<RL>::template f<F, T>, RE, RR>>;
            template <typename T, typename LL, typename LE, typename LR,
                        typename E, typename RL, typename RE, typename RR>
            using nn_1 = bnode<typename bun<LL>::template f<F, T>, LE,
                                bnode<LR, E, bnode<RL, RE, RR>>>;
            template <typename T, typename E>
            using l1 = blist<T, E>;
            template <typename T, typename E0, typename E1>
            using l2_0 = bnode<blist<T>, E0, blist<E1>>;
            template <typename T, typename E0, typename E1>
            using l2_1 = bnode<blist<E0>, T, blist<E1>>;
        };

        template <>
        struct bun<blist<>> {
            template <template <typename...> class F, typename T>
            using f = blist<T>;
        };
        template <typename E>
        struct bun<blist<E>> {
            template <template <typename...> class F, typename T>
            using f = bpush<F<T, E>::value, F>::template l1<T, E>;
        };
        template <typename E0, typename E1>
        struct bun<blist<E0, E1>> {
            template <template <typename...> class F, typename T>
            using f = bpush<F<T, E0>::value, F>::template l2_0<T, E0, E1>;
        };

        // Push a node. The node postion (either Left or Right) from the Edge
        // is determined by the type bpush<F<T, E>::value, F>::template
        // and will dispatch the correct node position by calling each
        // version's respective n<T, L, E, R> function.
        template <typename L, typename E, typename R>
        struct bun<bnode<L, E, R>> {
            template <template <typename...> class F, typename T>
            using f = bpush<F<T, E>::value, F>::template n<T, L, E, R>;
        };
        template <typename LL, typename LE, typename LR, typename E, typename RL,
                    typename RE, typename RR>
        struct bun<bnode<bnode<LL, LE, LR>, E, bnode<RL, RE, RR>>> {
            template <template <typename...> class F, typename T>
            using f = bpush<F<T, E>::value, F>::template nn<T, LL, LE, LR, E, RL,
                                                                        RE, RR>;
        };

        template <typename LLL, typename LLE, typename LLR, typename LE, typename LR,
                    typename E, typename... Ts>
        struct bun<bnode<bnode<bnode<LLL, LLE, LLR>, LE, LR>, E, blist<Ts...>>> {
            template <template <typename...> class F, typename T>
            using f = bpush<F<T, LE>::value, F>::template nn<T, LLL, LLE, LLR, LE,
                                                                        LR, E, blist<Ts...>>;
        };

        template <typename... Ts, typename E, typename RL, typename RE, typename RRL,
                    typename RRE, typename RRR>
        struct bun<bnode<blist<Ts...>, E, bnode<RL, RE, bnode<RRL, RRE, RRR>>>> {
            template <template <typename...> class F, typename T>
            using f = bpush<F<T, RE>::value, F>::template nn<T, blist<Ts...>, E, RL,
                                                                RE, RRL, RRE, RRR>;
        };

        // Prune branch

        // Remove leaf

        // Remove 

        template <typename LL, typename LE, typename LR, typename E, typename RL,
                    typename RE, typename RR>
        struct join7;

        template <typename... LL, typename LE, typename... LR, typename E, typename... RL,
                    typename RE, typename... RR>
        struct join7<blist<LL...>, LE, blist<LR...>, E, blist<RL...>, RE, blist<RR...>> {
            using type = blist<LL..., LE, LR..., E, RL..., RE, RR...>;
        };

        // Binary tree flattener metaclosures
        template <typename T>
        struct bflat;

        // Flatten single end node with Left, Edge, and Right
        template <typename L, typename E, typename R>
        struct bflat<bnode<L, E, R>> {
            using type = bflat<bnode<typename bflat<L>::type, E, typename bflat<R>::type>>::type;
        };

        // Flatten two nodes, Left and Right from Edge, and flatten their respective Left
        // and Right nodes with their Edges. Join the seven resulting types into
        // a blist, respecting their order.
        template <typename LL, typename LE, typename LR, typename E, typename RL,
                    typename RE, typename RR>
        struct bflat<bnode<bnode<LL, LE, LR>, E, bnode<RL, RE, RR>>> {
            using type = join7<typename bflat<LL>::type, LE, typename bflat<LR>::type,
                                    E, 
                                    typename bflat<RL>::type, RE, typename bflat<RR>::type
                                >::type;
        };

        // From a node, combine the Left and Right chlidren 
        // into a single blist.
        template <typename... L, typename E, typename... R>
        struct bflat<bnode<blist<L...>, E, blist<R...>>> {
            using type = blist<L..., E, R...>;
        };

        // Final combination of all the resulting types.
        template <typename... T>
        struct bflat<blist<T...>> {
            using type = blist<T...>;
        };

        template <typename T>
        using collapse_t = btree::bflat<T>::type;
    } // namespace btree

    // Push elements to btree
    template <typename F>
    struct element_pusher {};
    template <typename F>
    struct dispatch<2, element_pusher<F>> {
        template <typename T, typename U>
        using f = btree::bun<T>::template f<dispatch<2, F>::template f, U>;
    };
    template <template <typename...> class F>
    struct dispatch<2, element_pusher<lift_<F>>> {
        template <typename T, typename U>
        using f = btree::bun<T>::template f<F, U>;
    };
    template <template <typename...> class F>
    struct pusher {
        template <typename T, typename U>
        using f = btree::bun<T>::template f<F, U>;
    };
    template <template <typename...> class F, typename C = identity_,
                typename Initial = btree::blist<>>
    using make_binary_tree =
            push_front_<Initial, fold_left_<lift_<pusher<F>::template f>, C>>;
    template <typename C>
    using collapse_unpack = lift_<btree::collapse_t, unpack_<C>>;
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, sort_<lift_<F>, C>>
        : dispatch<N, make_binary_tree<F, collapse_unpack<C>, btree::blist<>>> {};
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, sort_<F, C>>
        : dispatch<N, make_binary_tree<dispatch<2, F>::template f, collapse_unpack<C>,
                                        btree::blist<>>> {};
} // namespace impl

BOOST_TMP_EXPORT template <typename... Fs>
struct tee_ {};
namespace impl { // tee_
    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                    typename dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
                    typename dispatch<find_dispatch(sizeof...(Ts)), L>::template f<Ts...>>;
    };
    // specialization for case where last closure is a forward
    template <typename N, typename C, typename... Fs>
    struct tee_impl<N, identity_, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Fs) + sizeof...(Ts)), C>::template
                    f<dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
                            Ts...>;
    };
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<1>, L, C, Fs...> {
        template <typename T0>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                    typename dispatch<1, Fs>::template f<T0>...,
                    typename dispatch<1, L>::template f<T0>>;
    };
    // specialization for case where last closure is a forward
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<1>, identity_, C, Fs...> {
        template <typename T0>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                    typename dispatch<1, Fs>::template f<T0>..., T0>;
    };
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<2>, L, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template
                        f<typename dispatch<2, Fs>::template f<T0, T1>...,
                        typename dispatch<2, L>::template f<T0, T1>>;
    };
    // specialization for case where last closure is a forward
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<2>, identity_, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 2), C>::template f<
                    typename dispatch<2, Fs>::template f<T0, T1>..., T0, T1>;
    };

    // in case the continuation is an and_

    template <bool b, typename C, typename... Fs>
    struct tee_and_impl;
    template <typename C, typename... Fs>
    struct tee_and_impl<false, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename... Fs>
    struct tee_and_impl<true, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_and_impl<true, C, F, Fs...> {
        template <typename... Ts>
        using f = tee_and_impl<dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
                Fs...>::template f<Ts...>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_and_impl_1;
    template <typename C, typename... Fs>
    struct tee_and_impl_1<false, C, Fs...> {
        template <typename T0>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename... Fs>
    struct tee_and_impl_1<true, C, Fs...> {
        template <typename T0>
        using f1 = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_and_impl_1<true, C, F, Fs...> {
        template <typename T0>
        using f = tee_and_impl<dispatch<1, F>::template f<T0>::value, C,
                                        Fs...>::template f<T0>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_and_impl_2;
    template <typename C, typename... Fs>
    struct tee_and_impl_2<false, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename... Fs>
    struct tee_and_impl_2<true, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_and_impl_2<true, C, F, Fs...> {
        template <typename T0, typename T1>
        using f = tee_and_impl<dispatch<2, F>::template f<T0, T1>::value, C,
                                        Fs...>::template f<T0, T1>;
    };

    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl<N, L, and_<identity_, C>, Fs...> : tee_and_impl<true, C, Fs..., L> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<1>, L, and_<identity_, C>, Fs...>
            : tee_and_impl_1<true, C, Fs..., L> {};
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<1>, identity_, and_<identity_, C>, Fs...>
            : tee_and_impl_1<true, C, Fs..., identity_> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<2>, L, and_<identity_, C>, Fs...>
            : tee_and_impl_2<true, C, Fs..., L> {};
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<2>, identity_, and_<identity_, C>, Fs...>
            : tee_and_impl_2<true, C, Fs..., identity_> {};

    // in case the continuation is an or_

    template <bool b, typename C, typename... Fs>
    struct tee_or_impl;
    template <typename C, typename... Fs>
    struct tee_or_impl<true, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename... Fs>
    struct tee_or_impl<false, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_or_impl<false, C, F, Fs...> {
        template <typename... Ts>
        using f = tee_or_impl<
                dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
                Fs...>::template f<Ts...>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_or_impl_1;
    template <typename C, typename... Fs>
    struct tee_or_impl_1<true, C, Fs...> {
        template <typename T0>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename... Fs>
    struct tee_or_impl_1<false, C, Fs...> {
        template <typename T0>
        using f1 = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_or_impl_1<false, C, F, Fs...> {
        template <typename T0>
        using f = tee_or_impl<dispatch<1, F>::template f<T0>::value, C,
                                        Fs...>::template f<T0>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_or_impl_2;
    template <typename C, typename... Fs>
    struct tee_or_impl_2<true, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename... Fs>
    struct tee_or_impl_2<false, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_or_impl_2<false, C, F, Fs...> {
        template <typename T0, typename T1>
        using f = tee_or_impl<dispatch<2, F>::template f<T0, T1>::value, C,
                                        Fs...>::template f<T0, T1>;
    };

    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl<N, L, or_<identity_, C>, Fs...> : tee_or_impl<false, C, Fs..., L> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<1>, L, or_<identity_, C>, Fs...>
            : tee_or_impl_1<false, C, Fs..., L> {};
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<1>, identity_, or_<identity_, C>, Fs...>
            : tee_or_impl_1<false, C, Fs..., identity_> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<2>, L, or_<identity_, C>, Fs...>
            : tee_or_impl_2<false, C, Fs..., L> {};

    template <std::size_t N, typename F0, typename F1, typename... Fs>
    struct dispatch<N, tee_<F0, F1, Fs...>>
        : dispatch<find_dispatch(sizeof...(Fs) + 2),
                    rotate_<sizet_<sizeof...(Fs)>, push_front_<sizet_<N>, lift_<tee_impl>>>>::
                    template f<F0, F1, Fs...> {};
} // namespace impl

BOOST_TMP_EXPORT template <typename M, typename C = identity_>
struct find_ {};
namespace impl {
    template<typename I, typename Ts>
    using index_helper = call_<unpack_index_<I>, Ts>;
    template<std::size_t N, typename M, typename C>
    struct dispatch<N, find_<M, C>> {
        template<typename T>
        using f = dispatch<N, unpack_<tee_<keys_<find_if_<is_<T>>>, values_<>, lift_<index_helper, C>>>>::template f<M>;
    };
} // namespace impl

template<typename T, typename SizeT>
using actual_array = std::array<std::remove_cvref_t<decltype(T::value)>, SizeT::value>;

// list_into_array_
BOOST_TMP_EXPORT template<typename... Ts>
struct list_into_array_ {};

template<typename... Ts>
struct list_into_array_<list_<Ts...>> {
    using arr = call_<tee_<i0_<>, size_<>, lift_<actual_array>>, Ts...>;

    static constexpr arr value = {Ts::value...};
};

BOOST_TMP_EXPORT template<typename F = identity_, typename C = listify_>
struct unique_ {};
namespace impl { // unique_
    template <typename T>
    struct unique_magic_type;

    // Our starting point; gets dropped off at the end.
    struct unique_super_base {
        static consteval bool contains(void *) {
            return false;
        }
    };
    template <typename Tail, typename T>
    struct unique_base : Tail {
        static consteval bool contains(unique_magic_type<T> *) {
            return true;
        }

        using Tail::contains;
    };

    template <typename T, typename U>
    using is_in_set = bool_<T::contains(static_cast<unique_magic_type<U> *>(0))>;

    using unique_push_if = if_<lift_<is_in_set>, front_<>, lift_<unique_base>>;

    template<std::size_t N, typename F, typename C>
    struct dispatch<N, unique_<F, C>> {
        template<typename... Ts>
        using f = dispatch<N, push_front_<unique_super_base, fold_left_<unique_push_if, flatten_<drop_<sizet_<1>, C>>>>>::template f<Ts...>;
    };
} // namespace impl

// FIXME: zip_ should have a dispatching functionality similar to
// rotate or other large dispatching functions.
// zip_ :
// Input params: Parameter pack
// Closure params: F - Metaclosure that accepts input parameter types in parameter pack.
//                 C - Continuation; default listify_
// Functional description:
// input  - T0, T1, ..., TN
// apply  - (invoke F on each element)
// result - list_<F<T0>, F<T1>, ..., F<TN>>
// Empty / default return type: list_<>
BOOST_TMP_EXPORT template <typename UnaryOp, typename C = listify_>
struct zip_ {};
namespace impl { // zip_
    template<typename F, typename C, typename T, typename U>
    struct zip2;
    template<typename F, typename C, typename...Ts, typename...Us>
    struct zip2<F, C, list_<Ts...>, list_<Us...>> {
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template
            f<typename dispatch<2, F>::template f<Ts, Us>...>;
    };
    template<typename F, typename C, typename T, typename U, typename V>
    struct zip3;
    template<typename F, typename C, typename... Ts, typename... Us, typename... Vs>
    struct zip3<F, C, list_<Ts...>, list_<Us...>, list_<Vs...>> {
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template
            f<typename dispatch<3, F>::template f<Ts, Us, Vs>...>;
    };
    template <typename F, typename C>
    struct dispatch<1, zip_<F, C>> : dispatch<1, unpack_<transform_<F, C>>> {};
    template <typename F, typename C>
    struct dispatch<2, zip_<F, C>> {
        template<typename T, typename U>
        using f = zip2<F, C, T, U>::f;
    };
    template<typename F, typename C>
    struct dispatch<3, zip_<F, C>> {
        template<typename T, typename U, typename V>
        using f = zip3<F, C, T, U, V>::f;
    };
} // namespace impl

// zip_with_index_ : Enumerates over a parameter pack, indexing each
// element starting at 0.
BOOST_TMP_EXPORT template <typename F = listify_, typename C = listify_>
struct zip_with_index_ {};
namespace impl { // zip_with_index_
    template <typename L>
    struct indexer;
    template <typename... Is>
    struct indexer<list_<Is...>> {
        template <typename F, template<typename...> class C, typename... Ts>
        using f = C<typename dispatch<2, F>::template f<Is, Ts>...>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, zip_with_index_<F, C>> {
        template <typename... Ts>
        using f = indexer<make_index_for_<sizeof...(Ts)>>::template f<
                F, dispatch<find_dispatch(sizeof...(Ts)), C>::template f, Ts...>;
    };
    template <std::size_t N, typename F, template <typename...> class C>
    struct dispatch<N, zip_with_index_<F, lift_<C>>> {
        template <typename... Ts>
        using f = indexer<make_index_for_<sizeof...(Ts)>>::template f<F, C, Ts...>;
    };
} // namespace impl

// partition_ : Given a unary predicate, separate a VPP into a list of two lists,
// with the first list being the elements where the predicate is true.
// Maintains order of elements.
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = listify_>
struct partition_ {};
namespace impl { // partition_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, partition_<F, C>> : dispatch<N, tee_<filter_<F>, remove_if_<F>, C>> {};
} // namespace impl

// stride_ : Get every nth element in a parameter pack, starting
// at zero.
// Input params: Parameter pack
// Closure params: S - Positive integer type denoting the step of the stride.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, T2, T3, T4, T5, ..., TN
// apply  -  (get every nth element)
// result -  T0, T(n), T(2n), T(3n), ..., T(m * n)
// Empty return type: list_<>
BOOST_TMP_EXPORT template<Sizable S = sizet_<0>, typename C = listify_>
struct stride_ {};
namespace impl { // stride_
    template<typename S, typename C = listify_, typename L = listify_>
    struct tee_drops_ {};
    template<std::size_t N, typename S, typename C, typename... Ts>
    struct dispatch<N, tee_drops_<S, list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<sizeof...(Us) / S::value + 1, tee_<index_<sizet_<Ts::value * S::value>>..., C>>::template f<Us...>;
    };
    template<typename S, typename C, typename... Ts>
    struct dispatch<0, tee_drops_<S, list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<0, tee_<i0_<>, C>>::template f<Us...>;
    };

    consteval std::size_t stride_div(std::size_t input_size, std::size_t stride_length) {
        return (input_size % stride_length) < 1
            ? input_size / stride_length
            : input_size / stride_length + 1;
    }

    template<std::size_t N, typename S, typename C>
    struct dispatch<N, stride_<S, C>> {
        template<typename... Ts>
        using f = dispatch<N, tee_drops_<S, make_index_for_<stride_div(sizeof...(Ts), S::value)>, C>>::template f<Ts...>;
    };
    template<typename S, typename C>
    struct dispatch<0, stride_<S, C>> {
        template<typename... Ts>
        using f = dispatch<0, tee_drops_<S, list_<sizet_<0>>, C>>::template f<>;
    };
} // namespace impl

// take_ :
BOOST_TMP_EXPORT template <Sizable N = sizet_<0>, typename C = listify_>
struct take_ {};
namespace impl { // take_
    template <std::size_t N, typename P, typename C>
    struct dispatch<N, take_<P, C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)),
                        rotate_<P, drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>>::template f<Ts...>;
    };
} // namespace impl

// take_last_ :
BOOST_TMP_EXPORT template<Sizable N = sizet_<0>, typename C = listify_>
struct take_last_ {};
namespace impl { // take_last_
    template<std::size_t N, typename P, typename C>
    struct dispatch<N, take_last_<P, C>> {
        template<typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>::template f<Ts...>;
    };
} // namespace impl

// take_list :
template<typename C = listify_>
struct take_list {};

BOOST_TMP_EXPORT template<typename UnaryPred, typename C = listify_>
struct take_while_ {};
namespace impl { // take_while_
    template<std::size_t N, typename C>
    struct dispatch<N, take_list<C>> {
        template<typename TakeValue, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), unpack_<take_<TakeValue, C>>>::template f<Ts...>;
    };

    template<std::size_t N, typename F, typename C>
    struct dispatch<N, take_while_<F, C>> : dispatch<N, tee_<find_if_not_<F>, listify_, take_list<C>>> {};
} // namespace impl

// drop_list_ :
template<typename C = listify_>
struct drop_list_ {};
namespace impl { // drop_list_
    template<std::size_t N, typename C>
    struct dispatch<N, drop_list_<C>> {
        template<typename DropValue, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), unpack_<drop_<DropValue, C>>>::template f<Ts...>;
    };
} // namespace impl

// drop_while_ :
BOOST_TMP_EXPORT template<typename F, typename C = listify_>
struct drop_while_ {};
namespace impl { // drop_while_
    template<std::size_t N, typename F, typename C>
    struct dispatch<N, drop_while_<F, C>> : dispatch<N, tee_<find_if_not_<F>, listify_, drop_list_<C>>> {};
} // namespace impl

// trim_ :
BOOST_TMP_EXPORT template<typename F, typename C = listify_>
struct trim_ {};
namespace impl { // trim_
    template<std::size_t N, typename F, typename C>
    struct dispatch<N, trim_<F, C>> : dispatch<N, drop_while_<F, reverse_<drop_while_<F, reverse_<C>>>>> {};
} // namespace impl

// drop_while_back_ :
BOOST_TMP_EXPORT template<typename F, typename C = listify_>
struct drop_while_back_ {};
namespace impl { // drop_while_back_
    template<std::size_t N, typename F, typename C>
    struct dispatch<N, drop_while_back_<F, C>> : dispatch<N, reverse_<drop_while_<F, reverse_<C>>>> {};
} // namespace impl

BOOST_TMP_EXPORT template<Sizable I = sizet_<0>, typename C = listify_>
struct split_ {};
namespace impl { // split_
    template<std::size_t N, typename I, typename C>
    struct dispatch<N, split_<I, C>> : dispatch<N, tee_<take_<I>, drop_<I>, listify_>> {};
} // namespace impl

// TODO: Add special cases:
// Comparison list is greater than the input list
// No input
// Empty comparison list
// starts_with_ :
BOOST_TMP_EXPORT template<typename L, typename C = identity_>
struct starts_with_ {};
namespace impl { // starts_with_
    template<std::size_t N, typename L, typename C = identity_>
    struct starts_with_impl;
    template<std::size_t N, typename C, typename... Ts>
    struct dispatch<N, starts_with_impl<N, list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<sizeof...(Us),
            take_<sizet_<sizeof...(Ts)>,
                lift_<list_, is_<list_<Ts...>, C>>>>::template f<Us...>;
    };
    template<std::size_t N, typename L, typename C>
    struct dispatch<N, starts_with_<L, C>> : dispatch<N, starts_with_impl<N, L, C>> {};
} // namespace impl

// ends_with_ :
BOOST_TMP_EXPORT template<typename L, typename C = identity_>
struct ends_with_ {};
namespace impl { // ends_with_
    template<std::size_t N, typename L, typename C = identity_>
    struct ends_with_impl;
    template<std::size_t N, typename C, typename... Ts>
    struct dispatch<N, ends_with_impl<N, list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<sizeof...(Us),
            reverse_<
                take_<sizet_<sizeof...(Ts)>,
                    reverse_<lift_<list_, is_<list_<Ts...>, C>>>>>>::template f<Us...>;
    };
    template<std::size_t N, typename L, typename C>
    struct dispatch<N, ends_with_<L, C>> : dispatch<N, ends_with_impl<N, L, C>> {};
} // namespace impl

// window_ :
BOOST_TMP_EXPORT template<Sizable StartIndex, Sizable Count, typename C = listify_>
struct window_ {};
namespace impl { // window_
    template<std::size_t N, typename StartIndex, typename Count, typename C>
    struct dispatch<N, window_<StartIndex, Count, C>> {
        template<typename... Ts>
        using f = dispatch<sizeof...(Ts), drop_<StartIndex, take_<Count, C>>>::template f<Ts...>;
    };
} // namespace impl

// chunk_ : Get every nth element in a parameter pack, starting
// at zero.
// Input params: Parameter pack
// Closure params: S - Positive integer type denoting the step of the stride.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, T2, T3, T4, T5, ..., TN
// apply  -  (get every nth element)
// result -  T0, T(n), T(2n), T(3n), ..., T(m * n)
// Empty return type: list_<>
BOOST_TMP_EXPORT template<Sizable S = sizet_<0>, typename C = listify_>
struct chunk_ {};
namespace impl { // chunk_
    consteval std::size_t chunk_div(std::size_t input_size, std::size_t chunk_length) {
        if((input_size % chunk_length < 1) && (input_size > chunk_length))
            return input_size / chunk_length;
        else if(input_size < chunk_length)
            return 1;
        else // remainder chunk
            return input_size / chunk_length + 1;
    }
    consteval std::size_t chunking_size(std::size_t current_index, std::size_t chunk_size, std::size_t val_count) {
        if(auto remainder = val_count % chunk_size; (remainder > 0) && ((current_index * chunk_size + remainder) == val_count))
            return remainder; // Return the last, unevenly chunked, elements.
        else
            return chunk_size;
    }
    template<typename S, typename C, typename... Ts>
    struct chunk_impl {};
    template<std::size_t N, typename S, typename C, typename... Ts>
    struct dispatch<N, chunk_impl<S, list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<sizeof...(Us),
            tee_<window_<sizet_<(Ts::value * S::value)>,
                        sizet_<chunking_size(Ts::value, S::value, sizeof...(Us))>>..., C>>::template f<Us...>;
    };
    template<std::size_t N, typename S, typename C>
    struct dispatch<N, chunk_<S, C>> {
        template<typename... Ts>
        using f = dispatch<sizeof...(Ts),
            chunk_impl<S, make_index_for_<chunk_div(sizeof...(Ts), S::value)>, C>>::template f<Ts...>;
    };
} // namespace impl

// TODO: Add incrementing by a number other than 1.
// slide_ : Given a window size W, form a list of lists where each individual
// list is W elements long, starting at index 0 and incrementing until the last
// list contains the last element.
// at zero.
// Input params: Parameter pack
// Closure params: W - Positive integer type denoting the window size.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, T2, T3, T4, T5, ..., TN
// apply  -  (get W elements starting at index 0, incrementing through until the last element)
// result -  L(T0, ..., TW), L(T1, ... T(W + 1)), ..., L(T(W - N), TN)
// Empty return type: list_<>
BOOST_TMP_EXPORT template<Sizable W = sizet_<0>, typename C = listify_>
struct slide_ {};
namespace impl { // slide_
    template<typename W, typename C = listify_, typename L = listify_>
    struct slide_impl {};
    template<std::size_t N, typename W, typename C, typename... Ts>
    struct dispatch<N, slide_impl<W, list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<sizeof...(Us), tee_<window_<Ts, W>..., C>>::template f<Us...>;
    };
    template<std::size_t N, typename W, typename C>
    struct dispatch<N, slide_<W, C>> {
        template<typename... Ts>
        using f = dispatch<N, slide_impl<W, make_index_for_<sizeof...(Ts) - W::value + 1>, C>>::template f<Ts...>;
    };
    template<typename W, typename C>
    struct dispatch<0, slide_<W, C>> {
        template<typename... Ts>
        using f = dispatch<0, slide_impl<W, list_<sizet_<0>>, C>>::template f<>;
    };
} // namespace impl

// contains_ : Given a type (V), return true_ / false_ on whether a given VPP
// contains the type V.
BOOST_TMP_EXPORT template <typename T, typename C = identity_>
struct contains_ {};
namespace impl { // contains_
    template <std::size_t N, typename T, typename C>
    struct dispatch<N, contains_<T, C>> : dispatch<N, or_<is_<T>, C>> {};
} // namespace impl

// contains_subrange_ :
BOOST_TMP_EXPORT template<typename L, typename C = identity_>
struct contains_subrange_ {};
namespace impl { // contains_subrange_
    template<std::size_t N, typename C, typename... Ts>
    struct dispatch<N, contains_subrange_<list_<Ts...>, C>> {
        template<typename... Us>
        using f = dispatch<sizeof...(Us), slide_<sizet_<sizeof...(Ts)>, contains_<list_<Ts...>, C>>>::template f<Us...>;
    };
} // namespace impl

// try_ :
BOOST_TMP_EXPORT template <template <typename...> class F, typename C = identity_>
struct try_ {};
template <typename T>
struct t_ {
    using type = T;
};
namespace impl { // try_
    template <template <typename...> class F, typename... Ts>
    t_<F<Ts...>> try_f(lift_<F>, list_<Ts...>);
    t_<nothing_> try_f(...);

    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, try_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<typename decltype(
                try_f(lift_<F>{}, list_<Ts...>{}))::type>;
    };
} // namespace impl

BOOST_TMP_EXPORT template<template<auto> typename ValueType, auto Value>
struct value_encap_t_ {
    using type = ValueType<Value>;
};

} // namespace boost::tmp
