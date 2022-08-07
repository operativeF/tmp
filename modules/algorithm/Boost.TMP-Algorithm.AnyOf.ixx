//  Copyright 2018-2019 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.AnyOf;

import :Algorithm.FindIf;
import :Base.Always;
import :Base.Bool;
import :Base.Identity;
import :Base.If;
import :Base.Logic;
import :Base.Nothing;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

// Given a unary predicate, return true_ / false_ on whether any elements
// in a VPP satisfy that predicate.
namespace boost::tmp {
    export template <typename F = identity_, typename C = identity_>
    struct any_of_ {};

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, any_of_<F, C>>
        : dispatch<N, or_<F, C>> {
    };
} // namespace boost::tmp

// TESTING:
namespace any_of_test {

} // namespace any_of_test
