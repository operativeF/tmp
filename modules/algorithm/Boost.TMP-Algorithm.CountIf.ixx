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

import :Algorithm.Transform;
import :Base.Always;
import :Base.Bool;
import :Base.Call;
import :Base.Dispatch;
import :Base.Identity;
import :Base.Integral;
import :Base.If;
import :Base.List;
import :Sequence.Join;
import :Sequence.Size;

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
namespace boost::tmp::test {
    // TODO: Put in helper partition.
    template <typename T>
    using is_even = bool_<(T::value % 2 == 0)>;

    template<typename T> requires(std::same_as<T, sizet_<0>>)
    struct NoEvenNumbers;

    template<typename T> requires(std::same_as<T, sizet_<3>>)
    struct HasThreeEvenNumbers;

    NoEvenNumbers<call_<count_if_<lift_<is_even>>, int_<1>, int_<3>>>;

    HasThreeEvenNumbers<call_<count_if_<lift_<is_even>>, int_<0>, int_<2>, int_<4>>>;
    
    // Empty input pack returns 0
    NoEvenNumbers<call_<count_if_<lift_<is_even>>>>;
} // namespace boost::tmp::test
