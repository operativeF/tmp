//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Partition;

import :Algorithm.Filter;
import :Algorithm.FunctionIf;
import :Algorithm.Tee;
import :Base.Types;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

// partition_ : Given a unary predicate, separate a VPP into a list of two lists,
// with the first list being the elements where the predicate is true.
// Maintains order of elements.
export template <typename F, typename C = listify_>
struct partition_ {};

// partition_ : implementation
namespace impl {

template <std::size_t N, typename F, typename C>
struct dispatch<N, partition_<F, C>> : dispatch<N, tee_<filter_<F>, remove_if_<F>, C>> {};

} // namespace impl

#ifdef TMP_COMPILE_TIME_TESTING
namespace test {

template<typename T> requires(std::same_as<T, list_<list_<int_<3>, int_<4>>, list_<int_<1>, int_<2>>>>)
struct SplitIntoTwoListWithGreaterThanTwo;

template <typename T>
using greater_than_two = bool_<(T::value > 2)>;

using partition_test_1 = SplitIntoTwoListWithGreaterThanTwo<call_<partition_<lift_<greater_than_two>>, int_<1>, int_<2>, int_<3>, int_<4>>>;

} // namespace test
#endif // TMP_COMPILE_TIME_TESTING

} // namespace boost::tmp
