//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
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

export module Boost.TMP:Algorithm.AllOf;

import :Algorithm.Logic;
import :Base.Types;

#if _MSC_VER
import std;
#endif

// Given a unary predicate, return true_ / false_ on whether all elements
// in a VPP satisfy that predicate.
namespace boost::tmp {
    export template <typename F, typename C = identity_>
    struct all_of_ {};
        
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, all_of_<F, C>> : dispatch<N, and_<F, C>> {};
} // namespace boost::tmp

// TESTING:
namespace all_of_test {

} // namespace all_of_test
