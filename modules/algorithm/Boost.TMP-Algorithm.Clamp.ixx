//  Copyright 2018-2019 Odin Holmes.
//            2020-2022 Thomas Figueroa.
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

export module Boost.TMP:Algorithm.Clamp;

import :Algorithm.RemoveIf;
import :Base.Call;
import :Base.Comparison;
import :Base.Types;

#if _MSC_VER
import std;
#endif

// Given a lower-bound type (L) and higher-bound type (H), and that both types
// are less than and greater than comparable, remove all types less than L and all types
// greater than H from a given VPP.
// The VPP values must also satisfy being less than and greater than comparable.
namespace boost::tmp {
    export template <typename L, typename H, typename C = identity_>
    struct clamp_ {};

    template <std::size_t N, typename L, typename H, typename C>
    struct dispatch<N, clamp_<L, H, C>>
        : dispatch<N, remove_if_<range_lo_hi_<L, H, C>>> {};
} // namespace boost::tmp

// TESTING:
namespace clamp_test {
    using namespace boost::tmp;
    
    template<typename T> requires(std::same_as<T, list_<uint_<4>>>)
    struct ListWithOnlyFour;

    using test_one = ListWithOnlyFour<call_<clamp_<uint_<3>, uint_<10>>, uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>>;
} // namespace clamp_test
