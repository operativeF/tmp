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

export module Boost.TMP:Algorithm.ReplaceIf;

import :Algorithm.Logic;
import :Algorithm.Transform;
import :Base.Types;

import :TestHelpers;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER

/// \brief Given a variadic parameter pack, replace every value that fulfills
/// the predicate F with the value Input.
namespace boost::tmp {
    export template <typename Input, typename F, typename C = listify_>
    struct replace_if_ {};

    template <std::size_t N, typename Input, typename F, typename C>
    struct dispatch<N, replace_if_<Input, F, C>>
              : dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
} // namespace boost::tmp

// TESTING:
namespace replace_if_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, list_<uint_<1>, char_<'c'>, uint_<1>>>)
    struct ReplaceTwoWithC;

    template<typename T> requires(std::same_as<T, list_<>>)
    struct EmptyPackReturnsAnEmptyList;

    using test_one = ReplaceTwoWithC<call_<replace_if_<char_<'c'>, lift_<utils::is_even>>, uint_<1>, uint_<2>, uint_<1>>>;

    using test_two = EmptyPackReturnsAnEmptyList<call_<replace_if_<char_<'c'>, lift_<utils::is_even>>>>;

} // namespace replace_if_test
