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

export module Boost.TMP:Sequence.PushFront;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// push_front_ :
export template <typename T, typename C = listify_>
struct push_front_ {};

// push_front_ : implementation
template <std::size_t N, typename T, typename C>
struct dispatch<N, push_front_<T, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<T, Ts...>;
};
} // namespace boost::tmp

// TESTING:
namespace push_front_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, list_<int_<4>, int_<1>, int_<2>>>)
    struct PushFourToFront;

    template<typename T> requires(std::same_as<T, list_<int_<1>>>)
    struct PushOneToEmptyPack;

    using test_one = PushFourToFront<call_<push_front_<int_<4>>, int_<1>, int_<2>>>;

    using test_two = PushOneToEmptyPack<call_<push_front_<int_<1>>>>;
} // namespace push_front_test
