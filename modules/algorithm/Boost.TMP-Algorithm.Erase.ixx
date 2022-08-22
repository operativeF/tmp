//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Erase;

import :Algorithm.PushPop;
import :Algorithm.Rotate;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
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
export template <typename N = sizet_<0>, typename C = listify_>
struct erase_ {};

// erase_ : implementation
namespace impl {

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

namespace test {

template<typename T> requires(std::same_as<T, list_<int_<2>, int_<3>>>)
struct EraseFirstElement;

// Erasing an element from a list with a single element will always result in empty list.
template<typename T> requires(std::same_as<T, list_<>>)
struct EraseSingleElement;

// UNDER RECONSIDERATION: Returns list_<nothing_> if no input is given.
template<typename T> requires(std::same_as<T, list_<nothing_>>)
struct EraseEmptyPackReturnsNothingType;

using erase_test_1   = EraseFirstElement<call_<erase_<sizet_<0>>, int_<1>, int_<2>, int_<3>>>;

using erase_test_2   = EraseSingleElement<call_<erase_<sizet_<0>>, int_<0>>>;

using erase_test_3   = EraseEmptyPackReturnsNothingType<call_<erase_<sizet_<0>>>>;

} // namespace test

} // namespace boost::tmp
