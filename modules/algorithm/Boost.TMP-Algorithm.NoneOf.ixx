//  Copyright 2018-2019 Odin Holmes.
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
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.NoneOf;

import :Algorithm.Logic;
import :Base.Types;

import :TestHelpers;

#if _MSC_VER
import std;
#endif

// Given a predicate (F), return true_ / false_ if none
// of the elements in a VPP satisfy the predicate F.
namespace boost::tmp {
    export template <typename F, typename C = identity_>
    struct none_of_ {};

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, none_of_<F, C>> : dispatch<N, and_<F, not_<C>>> {};
} // namespace boost::tmp

// TESTING:
namespace none_of_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, false_>)
    struct NoneOfTheNumbersAreOdd;

    template<typename T> requires(std::same_as<T, true_>)
    struct NoneOfTheNumbersAreEven;

    // Conversely, all of the numbers are even.
    using test_one = NoneOfTheNumbersAreOdd<call_<none_of_<lift_<utils::is_even>>, int_<2>, int_<100>, int_<4>, int_<500>>>;

    // Conversely, all of the numbers are odd.
    using test_two = NoneOfTheNumbersAreEven<call_<none_of_<lift_<utils::is_even>>, int_<1>, int_<3>>>;
} // namespace none_of_test
