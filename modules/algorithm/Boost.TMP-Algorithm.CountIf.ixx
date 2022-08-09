//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.CountIf;

import :Algorithm.Logic;
import :Algorithm.Transform;
import :Base.Types;
import :Sequence.Join;
import :Sequence.Size;

import :TestHelpers;

#if _MSC_VER
import std;
#endif

/// \brief Given a predicate F, check the variadic parameter pack passed in and count
/// each time that the predicate holds true. Returns n counts as sizet_<n>.
/// \example
///
namespace boost::tmp {
    export template <typename F, typename C = identity_>
    struct count_if_ {};
    
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, count_if_<F, C>>
        : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
                                    join_<size_<C>>>> {};
} // namespace boost::tmp

// TESTING:
namespace count_if_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, sizet_<0>>)
    struct NoEvenNumbers;

    template<typename T> requires(std::same_as<T, sizet_<3>>)
    struct HasThreeEvenNumbers;

    using test_one  = NoEvenNumbers<call_<count_if_<lift_<utils::is_even>>, int_<1>, int_<3>>>;

    using test_two  = HasThreeEvenNumbers<call_<count_if_<lift_<utils::is_even>>, int_<0>, int_<2>, int_<4>>>;
    
    // Empty input pack returns 0
    using test_three = NoEvenNumbers<call_<count_if_<lift_<utils::is_even>>>>;
} // namespace count_if_test
