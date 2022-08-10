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

export module Boost.TMP:Algorithm.PushPop;

import :Algorithm.Drop;
import :Algorithm.Rotate;
import :Base.Types;

namespace boost::tmp {
// push_back_ :
export template <typename T, typename C = listify_>
struct push_back_ {};

// push_back_ : implementation
template <std::size_t N, typename T, typename C>
struct dispatch<N, push_back_<T, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
};

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

// push_front_ :
export template <typename T, typename C = listify_>
struct push_front_ {};

// push_front_ : implementation
template <std::size_t N, typename T, typename C>
struct dispatch<N, push_front_<T, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<T, Ts...>;
};

// TODO: Implement this.
// pop_back_ :
// export template <typename C = listify_>
// struct pop_back_ {};

// // pop_back_ : implementation
// template <std::size_t N, typename C>
// struct dispatch<N, pop_back_<C>> {
// 	template <typename T, typename... Ts>
// 	using f = typename dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
// };
// template <typename C>
// struct dispatch<0, pop_back_<C>> {
// 	template <typename... Ts>
// 	using f = typename dispatch<1, C>::template f<nothing_>;
// };

} // namespace boost::tmp

namespace push_pop_tests {
using namespace boost::tmp;

// push_back_ tests
template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, char_<'c'>>>)
struct PushBack_C {};

using push_back_test_1 = PushBack_C<call_<push_back_<char_<'c'>>, int_<1>, int_<2>>>;

// pop_front_ tests
template<typename T> requires(std::same_as<T, list_<>>)
struct NoElementsLeft;

template<typename T> requires(std::same_as<T, list_<nothing_>>)
struct EmptyPackReturnsListWithNothingType;

// Pop front off of single element list to return an empty list.
using pop_front_test_1 = NoElementsLeft<call_<pop_front_<>, list_<int_<1>>>>;

// Pop front off of empty list_ to return an empty list_
using pop_front_test_2 = NoElementsLeft<call_<pop_front_<>, list_<>>>;

// UNDER CONSIDERATION: Removal / modification of behavior of
// pop_front_ on no input. Currently returns a list_<nothing_>
using pop_front_test_3 = EmptyPackReturnsListWithNothingType<call_<pop_front_<>>>;

// push_front tests
template<typename T> requires(std::same_as<T, list_<int_<4>, int_<1>, int_<2>>>)
struct PushFourToFront;

template<typename T> requires(std::same_as<T, list_<int_<1>>>)
struct PushOneToEmptyPack;

using push_front_test_1 = PushFourToFront<call_<push_front_<int_<4>>, int_<1>, int_<2>>>;

using push_front_test_2 = PushOneToEmptyPack<call_<push_front_<int_<1>>>>;

} // namespace push_pop_tests
