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

export module Boost.TMP:Algorithm.Logic;

import :Algorithm.Filter;
import :Algorithm.Foldey;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

} // namespace boost::tmp

namespace logic_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, false_>)
struct AllNumbersOdd;

template<typename T> requires(std::same_as<T, true_>)
struct AllNumbersEven;

template<typename T> requires(std::same_as<T, true_>)
struct OneNumberEven;

template<typename T> requires(std::same_as<T, true_>)
struct OneNumberOdd;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using and_test_1 = AllNumbersOdd<call_<and_<lift_<is_even>>, int_<1>, int_<1>, int_<1>>>;

using and_test_2 = AllNumbersEven<call_<and_<lift_<is_even>>, int_<2>, int_<2>, int_<2>>>;

using or_test_1 = OneNumberEven<call_<or_<lift_<is_even>>, int_<1>, int_<2>, int_<1>>>;

using or_test_2 = OneNumberOdd<call_<or_<lift_<is_even>>, int_<2>, int_<1>, int_<2>>>;

// Contains tests
template<typename T> requires(std::same_as<T, false_>)
struct DoesNotContainType;

template<typename T> requires(std::same_as<T, true_>)
struct ContainsType;

using contains_test_1   = DoesNotContainType<call_<contains_<int_<0>>, int_<1>>>;

using contains_test_2   = ContainsType<call_<contains_<int_<2>>, int_<0>, int_<1>, int_<2>>>;

using contains_test_3   = DoesNotContainType<call_<contains_<int_<1>>>>;

// template<int A, int B>
// struct two_ints {
//     int a{A};
//     int b{B};
// };

// false_{} = call_<less_f_<lift_<std::alignment_of>>, two_ints<1, 2>, char_<'c'>>{};
// true_{}  = call_<less_f_<lift_<std::alignment_of>>, char_<'c'>,     two_ints<1, 2>>{};

template<typename T> requires(std::same_as<T, false_>)
struct NoneOfTheNumbersAreOdd;

template<typename T> requires(std::same_as<T, true_>)
struct NoneOfTheNumbersAreEven;

using none_of_test_1 = NoneOfTheNumbersAreOdd<call_<none_of_<lift_<is_even>>, int_<2>, int_<100>, int_<4>, int_<500>>>;

using none_of_test_2 = NoneOfTheNumbersAreEven<call_<none_of_<lift_<is_even>>, int_<1>, int_<3>>>;
} // namespace logic_test
