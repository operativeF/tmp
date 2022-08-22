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

export module Boost.TMP:Algorithm.Size;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// size_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default identity_
// Functional description:
// input  - T0, T1, ..., TN (Ts...)
// apply  - (get number of elements in parameter pack)
// result - sizet_<sizeof...(Ts)>
// Empty return type: sizet_<0>
export template <typename C = identity_>
struct size_ {};

// size_ : implementation
namespace impl {

template <std::size_t N, typename C>
struct dispatch<N, size_<C>> {
    template <typename... Ls>
    using f = dispatch<1, C>::template f<sizet_<sizeof...(Ls)>>;
};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, sizet_<3>>)
struct SizeThreeElementsInPack;

template<typename T> requires(std::same_as<T, sizet_<0>>)
struct SizeEmptyPackIsZero;

using size_test_1 = SizeThreeElementsInPack<call_<size_<>, int_<0>, int_<2>, int_<4>>>;

// No input list is zero size.
using size_test_2 = SizeEmptyPackIsZero<call_<size_<>>>;

} // namespace test

} // namespace boost::tmp
