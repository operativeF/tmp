//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Sequence.PopFront;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// pop_front_ :
export template <typename C = listify_>
struct pop_front_ {};

// pop_front_ : implementation
template <std::size_t N, typename C>
struct dispatch<N, pop_front_<C>> {
    template <typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
};
// TODO: Should this be kept? This differs from the behavior of popping
// the front off of an empty list (which results in an empty list).
// This, however, will return a list_<nothing_>
template <typename C>
struct dispatch<0, pop_front_<C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<nothing_>;
};
} // namespace boost::tmp

// TESTING:
namespace pop_front_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, list_<>>)
    struct NoElementsLeft;

    template<typename T> requires(std::same_as<T, list_<nothing_>>)
    struct EmptyPackReturnsListWithNothingType;

    // Pop front off of single element list to return an empty list.
    using test_one = NoElementsLeft<call_<pop_front_<>, list_<int_<1>>>>;

    // Pop front off of empty list_ to return an empty list_
    using test_two = NoElementsLeft<call_<pop_front_<>, list_<>>>;

    // UNDER CONSIDERATION: Removal / modification of behavior of
    // pop_front_ on no input. Currently returns a list_<nothing_>
    using test_three = EmptyPackReturnsListWithNothingType<call_<pop_front_<>>>;
} // namespace pop_front_test
