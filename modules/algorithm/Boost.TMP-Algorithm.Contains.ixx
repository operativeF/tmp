//  Copyright 2018 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Contains;

import :Algorithm.Comparison;
import :Algorithm.Logic;
import :Base.Types;

#if _MSC_VER
import std;
#endif

// Given a type (V), return true_ / false_ on whether a given VPP
// contains the type V.
namespace boost::tmp {
    export template <typename T, typename C = identity_>
    struct contains_ {};

    template <std::size_t N, typename T, typename C>
    struct dispatch<N, contains_<T, C>> : dispatch<N, or_<is_<T>, C>> {};
} // namespace boost::tmp

// TESTING:
namespace contains_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, false_>)
    struct DoesNotContainType;

    template<typename T> requires(std::same_as<T, true_>)
    struct ContainsType;

    using test_one   = DoesNotContainType<call_<contains_<int_<0>>, int_<1>>>;

    using test_two   = ContainsType<call_<contains_<int_<2>>, int_<0>, int_<1>, int_<2>>>;

    using test_three = DoesNotContainType<call_<contains_<int_<1>>>>;
    
} // namespace contains_test
