//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#include <utility>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Join;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
export template <typename C = listify_>
struct join_ {};

export template<typename C = listify_>
struct join_seq_ {};

template<std::size_t... Is>
using IndexSeq = std::index_sequence<Is...>;

export template<typename... Ts>
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

} // namespace boost::tmp

// TESTING:
namespace join_test {
using namespace boost::tmp;

// TODO: Implement join_test
// using joined_sequences = call_<join_seq_<lift_<into_sequence>>, std::index_sequence<1, 2>, std::index_sequence<3, 4>>;

// joined_sequences{} = std::index_sequence<1, 2, 3, 4>{};
} // namespace join_test
