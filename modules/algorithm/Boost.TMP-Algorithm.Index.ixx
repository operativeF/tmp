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

export module Boost.TMP:Algorithm.Index;

import :Algorithm.Drop;
import :Algorithm.Unpack;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
export template<typename I, typename C = identity_>
struct index_ {};
export template<typename I, typename C = identity_>
using unpack_index_ = unpack_<index_<I, C>>;
export template<typename C = identity_>
using front_ = index_<sizet_<0>, C>;

export template<typename C = identity_>
using i0_ = index_<sizet_<0>, C>;
export template<typename C = identity_>
using i1_ = index_<sizet_<1>, C>;
export template<typename C = identity_>
using i2_ = index_<sizet_<2>, C>;
export template<typename C = identity_>
using i3_ = index_<sizet_<3>, C>;
export template<typename C = identity_>
using i4_ = index_<sizet_<4>, C>;
export template<typename C = identity_>
using i5_ = index_<sizet_<5>, C>;
export template<typename C = identity_>
using i6_ = index_<sizet_<6>, C>;
export template<typename C = identity_>
using i7_ = index_<sizet_<7>, C>;
export template<typename C = identity_>
using ui0_ = unpack_<index_<sizet_<0>, C>>;
export template<typename C = identity_>
using ui1_ = unpack_<index_<sizet_<1>, C>>;
export template<typename C = identity_>
using ui2_ = unpack_<index_<sizet_<2>, C>>;
export template<typename C = identity_>
using ui3_ = unpack_<index_<sizet_<3>, C>>;
export template<typename C = identity_>
using ui4_ = unpack_<index_<sizet_<4>, C>>;
export template<typename C = identity_>
using ui5_ = unpack_<index_<sizet_<5>, C>>;
export template<typename C = identity_>
using ui6_ = unpack_<index_<sizet_<6>, C>>;
export template<typename C = identity_>
using ui7_ = unpack_<index_<sizet_<7>, C>>;

template <std::size_t N, typename I, typename C>
struct dispatch<N, index_<I, C>> : dispatch<N, drop_<I, front_<C>>> {};

template <std::size_t N, typename C>
struct dispatch<N, index_<nothing_, C>> {
    template <typename... Ts>
    using f = nothing_;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<0>, C>> {
    template <typename T0, typename... Ts>
    using f = dispatch<1, C>::template f<T0>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<1>, C>> {
    template <typename T0, typename T1, typename... Ts>
    using f = dispatch<1, C>::template f<T1>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<2>, C>> {
    template <typename T0, typename T1, typename T2, typename... Ts>
    using f = dispatch<1, C>::template f<T2>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<3>, C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
    using f = dispatch<1, C>::template f<T3>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<4>, C>> {
    template<typename T0, typename T1, typename T2, typename T3,
                typename T4, typename... Ts>
    using f = dispatch<1, C>::template f<T4>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<5>, C>> {
    template<typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename... Ts>
    using f = dispatch<1, C>::template f<T5>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<6>, C>> {
    template<typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename... Ts>
    using f = dispatch<1, C>::template f<T6>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<7>, C>> {
    template <typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename T7, typename... Ts>
    using f = dispatch<1, C>::template f<T7>;
};
} // namespace boost::tmp

// TESTING:
namespace index_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, int_<3>>)
struct ElementAtIndexTwoIsThree;

template<typename T> requires(std::same_as<T, int_<1>>)
struct UnpackedElementAtIndexZeroIsOne;

template<typename T> requires(std::same_as<T, int_<1>>)
struct ElementAtFrontIsOne;

// Get index 2 of pack (int_<3>)
using test_one = ElementAtIndexTwoIsThree<call_<index_<uint_<2>>, int_<1>, char_<'c'>, int_<3>, int_<4>>>;

// Unpack simple_list, then take index 0
using test_two = UnpackedElementAtIndexZeroIsOne<call_<ui0_<>, list_<int_<1>, int_<2>, int_<3>>>>;

// Get first element of pack
using test_three = ElementAtFrontIsOne<call_<front_<>, int_<1>, int_<2>, int_<3>>>;
} // namespace index_test
