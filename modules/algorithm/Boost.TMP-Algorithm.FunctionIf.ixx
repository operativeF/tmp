//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#include <limits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.FunctionIf;

import :Algorithm.Filter;
import :Algorithm.Join;
import :Algorithm.Logic;
import :Algorithm.Size;
import :Algorithm.Transform;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

} // namespace boost::tmp

// TESTING:
namespace remove_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<3>>>)
struct OnlyOddNumbersLeft;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;


using test_one = OnlyOddNumbersLeft<call_<remove_if_<lift_<is_even>>, int_<1>, int_<2>, int_<3>>>;
} // namespace remove_if_test

// TESTING:
namespace count_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, sizet_<0>>)
struct NoEvenNumbers;

template<typename T> requires(std::same_as<T, sizet_<3>>)
struct HasThreeEvenNumbers;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using test_one  = NoEvenNumbers<call_<count_if_<lift_<is_even>>, int_<1>, int_<3>>>;

using test_two  = HasThreeEvenNumbers<call_<count_if_<lift_<is_even>>, int_<0>, int_<2>, int_<4>>>;

// Empty input pack returns 0
using test_three = NoEvenNumbers<call_<count_if_<lift_<is_even>>>>;
} // namespace count_if_test

// TESTING:
namespace replace_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<uint_<1>, char_<'c'>, uint_<1>>>)
struct ReplaceTwoWithC;

template<typename T> requires(std::same_as<T, list_<>>)
struct EmptyPackReturnsAnEmptyList;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using test_one = ReplaceTwoWithC<call_<replace_if_<char_<'c'>, lift_<is_even>>, uint_<1>, uint_<2>, uint_<1>>>;

using test_two = EmptyPackReturnsAnEmptyList<call_<replace_if_<char_<'c'>, lift_<is_even>>>>;
} // namespace replace_if_test

// TESTING:
namespace find_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, sizet_<3>>)
struct EvenNumberAtPositionThree;

template<typename T> requires(std::same_as<T, nothing_>)
struct ReturnNothingForNoValueFound;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using test_one = EvenNumberAtPositionThree<call_<find_if_<lift_<is_even>>, int_<1>, int_<1>, int_<1>, int_<2>>>;

// find_if_ returns nothing_ when there is no value found that satisfies the predicate.
using test_two = ReturnNothingForNoValueFound<call_<find_if_<lift_<is_even>>, int_<1>>>;

template<typename T> requires(std::same_as<T, sizet_<2>>)
struct OddNumberAtPositionTwo;

template<typename T> requires(std::same_as<T, nothing_>)
struct ReturnNothingForNoValueFound;

using find_if_not_test_1 = OddNumberAtPositionTwo<call_<find_if_not_<lift_<is_even>>, int_<2>, int_<4>, int_<1>, int_<2>>>;

// find_if_ returns nothing_ when there is no value found that satisfies the predicate.
using find_if_not_test_2 = ReturnNothingForNoValueFound<call_<find_if_not_<lift_<is_even>>, int_<2>>>;

} // namespace find_if_test
