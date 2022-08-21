//  Copyright 2018 Odin Holmes.
//			  2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Filter;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

} // namespace boost::tmp

// TESTING:
namespace filter_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<2>, int_<4>, int_<6>, int_<8>, int_<10>>>)
struct FilterOutOddNumbers;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using test_one = FilterOutOddNumbers<call_<filter_<lift_<is_even>>,
            int_<1>, int_<2>, int_<3>, int_<4>, int_<5>,
            int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>>;
} // namespace filter_test
