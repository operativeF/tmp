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

import :Algorithm.Index;
import :Algorithm.Transform;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

// keys_ :
export template<typename C = listify_>
struct keys_ {};

// keys_ : implementation
template <std::size_t N, typename C>
struct dispatch<N, keys_<C>> : dispatch<N, transform_<ui0_<>, C>> {};

// values_ :
export template<typename C = listify_>
struct values_ {};

// values_ : implementation
template <std::size_t N, typename C>
struct dispatch<N, values_<C>> : dispatch<N, transform_<ui1_<>, C>> {};

// nth_values_ :
export template<typename I, typename C = listify_>
struct nth_values_ {};

// nth_values_ : implementation
template <std::size_t N, typename I, typename C>
struct dispatch<N, nth_values_<I, C>> : dispatch<N, transform_<unpack_index_<I>, C>> {};

} // namespace boost::tmp

namespace nth_values_tests {

using namespace boost::tmp;

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

} // namespace keys_test
