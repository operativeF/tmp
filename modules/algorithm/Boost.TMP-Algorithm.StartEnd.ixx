//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.StartEnd;

import :Algorithm.Logic;
import :Algorithm.Reverse;
import :Algorithm.Take;
import :Base.Types;

namespace boost::tmp {

// TODO: Add special cases:
// Comparison list is greater than the input list
// No input
// Empty comparison list
// starts_with_ :
export template<typename L, typename C = identity_>
struct starts_with_ {};

namespace impl {

template<std::size_t N, typename L, typename C = identity_>
struct starts_with_impl;

template<std::size_t N, typename C, typename... Ts>
struct dispatch<N, starts_with_impl<N, list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<sizeof...(Us),
        take_<sizet_<sizeof...(Ts)>,
            lift_<list_, is_<list_<Ts...>, C>>>>::template f<Us...>;
};

template<std::size_t N, typename L, typename C>
struct dispatch<N, starts_with_<L, C>> : dispatch<N, starts_with_impl<N, L, C>> {};

} // namespace impl

// ends_with :
export template<typename L, typename C = identity_>
struct ends_with_ {};

namespace impl {

template<std::size_t N, typename L, typename C = identity_>
struct ends_with_impl;

template<std::size_t N, typename C, typename... Ts>
struct dispatch<N, ends_with_impl<N, list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<sizeof...(Us),
        reverse_<
            take_<sizet_<sizeof...(Ts)>,
                reverse_<lift_<list_, is_<list_<Ts...>, C>>>>>>::template f<Us...>;
};

template<std::size_t N, typename L, typename C>
struct dispatch<N, ends_with_<L, C>> : dispatch<N, ends_with_impl<N, L, C>> {};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, true_>)
struct StartsWithAB;

template<typename T> requires(std::same_as<T, false_>)
struct DoesNotStartWithAD;

template<typename T> requires(std::same_as<T, true_>)
struct EndsWithBD;

template<typename T> requires(std::same_as<T, false_>)
struct DoesNotEndWithAD;

using starts_with_test_1 = StartsWithAB<call_<starts_with_<list_<char_<'A'>, char_<'B'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

using starts_with_test_2 = DoesNotStartWithAD<call_<starts_with_<list_<char_<'A'>, char_<'D'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

using ends_with_test_1 = EndsWithBD<call_<starts_with_<list_<char_<'A'>, char_<'B'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

using ends_with_test_2 = DoesNotEndWithAD<call_<starts_with_<list_<char_<'A'>, char_<'D'>>>, char_<'A'>, char_<'B'>, char_<'D'>>>;

} // namespace test

} // namespace boost::tmp
