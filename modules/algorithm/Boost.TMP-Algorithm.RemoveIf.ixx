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
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.RemoveIf;

import :Algorithm.Filter;
import :Algorithm.Logic;
import :Base.Types;

import :TestHelpers;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// remove_if_ : Given a predicate F, check the variadic parameter pack passed in
// and remove the value if the predicate holds true.
export template <typename F, typename C = listify_>
struct remove_if_ {};

// remove_if_ : implementation
template<std::size_t N, typename F, typename C>
struct dispatch<N, remove_if_<F, C>>
        : dispatch<N, filter_<if_<F, always_<false_>, always_<true_>>, C>> {};
} // namespace boost::tmp

// TESTING:
namespace remove_if_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, list_<int_<1>, int_<3>>>)
    struct OnlyOddNumbersLeft;

    using test_one = OnlyOddNumbersLeft<call_<remove_if_<lift_<utils::is_even>>, int_<1>, int_<2>, int_<3>>>;
} // namespace remove_if_test

