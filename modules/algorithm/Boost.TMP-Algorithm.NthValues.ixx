//  Copyright 2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.NthValues;

import :Algorithm.Core;
import :Base.Types;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

// keys_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default listify_
// Functional description:
// input  - T0<t00, t01, ...>, T1<t10, t11, ...>, ..., TN<tN0, tN1, ...>
// apply  - (get 1st element from each element)
// result - list_<t00, t10, ..., tN0>
// Empty return type: list_<>
export template<typename C = listify_>
struct keys_ {};

// keys_ : implementation
namespace impl {

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
export template<typename C = listify_>
struct values_ {};

// values_ : implementation
namespace impl {

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
export template<typename I, typename C = listify_>
struct nth_values_ {};

// nth_values_ : implementation
namespace impl {

template <std::size_t N, typename I, typename C>
struct dispatch<N, nth_values_<I, C>> : dispatch<N, transform_<unpack_index_<I>, C>> {};

} // namespace impl

#ifdef TMP_COMPILE_TIME_TESTING
namespace test {

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>>>)
struct KeysOfMap;

template<typename T> requires(std::same_as<T, list_<int_<44>, int_<45>>>)
struct ValuesOfMap;

template<typename T> requires(std::same_as<T, list_<int_<22>, int_<23>>>)
struct IndexTwoValuesList;

using keys_test_1 = KeysOfMap<call_<keys_<>, list_<int_<1>, int_<22>>, list_<int_<2>, int_<10>>>>;

using values_test_1 = ValuesOfMap<call_<values_<>, list_<int_<1>, int_<44>>, list_<int_<2>, int_<45>>>>;

using nth_values_test_1 = IndexTwoValuesList<call_<nth_values_<sizet_<2>>,
                                                   list_<int_<1>, int_<22>, int_<22>>,
                                                   list_<int_<2>, int_<10>, int_<23>>>>;

} // namespace test
#endif // TMP_COMPILE_TIME_TESTING

} // namespace boost::tmp
