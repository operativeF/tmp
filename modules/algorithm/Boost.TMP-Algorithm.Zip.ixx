//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Zip;

import :Algorithm.MakeSequence;
import :Algorithm.Transform;
import :Algorithm.Unpack;
import :Base.Types;

#if _MSC_VER
import std;
#endif

// FIXME: zip_ should have a dispatching functionality similar to
// rotate or other large dispatching functions.

namespace boost::tmp {
// zip_ :
// Input params: Parameter pack
// Closure params: F - Metaclosure that accepts input parameter types in parameter pack.
//                 C - Continuation; default listify_
// Functional description:
// input  - T0, T1, ..., TN
// apply  - (invoke F on each element)
// result - list_<F<T0>, F<T1>, ..., F<TN>>
// Empty / default return type: list_<>
export template <typename F, typename C = listify_>
struct zip_ {};

// zip_ : implementation
namespace impl {

template<typename F, typename C, typename T, typename U>
struct zip2;
template<typename F, typename C, typename...Ts, typename...Us>
struct zip2<F, C, list_<Ts...>, list_<Us...>> {
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template
        f<typename dispatch<2, F>::template f<Ts, Us>...>;
};
template<typename F, typename C, typename T, typename U, typename V>
struct zip3;
template<typename F, typename C, typename... Ts, typename... Us, typename... Vs>
struct zip3<F, C, list_<Ts...>, list_<Us...>, list_<Vs...>> {
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template
        f<typename dispatch<3, F>::template f<Ts, Us, Vs>...>;
};
template <typename F, typename C>
struct dispatch<1, zip_<F, C>> : dispatch<1, unpack_<transform_<F, C>>> {};
template <typename F, typename C>
struct dispatch<2, zip_<F, C>> {
    template<typename T, typename U>
    using f = zip2<F, C, T, U>::f;
};
template<typename F, typename C>
struct dispatch<3, zip_<F, C>> {
    template<typename T, typename U, typename V>
    using f = zip3<F, C, T, U, V>::f;
};

} // namespace impl

// zip_with_index_ : Enumerates over a parameter pack, indexing each
// element starting at 0.
export template <typename F = listify_, typename C = listify_>
struct zip_with_index_ {};

// zip_with_index_ : implementation
namespace impl {

template <typename L>
struct indexer;
template <typename... Is>
struct indexer<list_<Is...>> {
    template <typename F, template<typename...> class C, typename... Ts>
    using f = C<typename dispatch<2, F>::template f<Is, Ts>...>;
};
template <std::size_t N, typename F, typename C>
struct dispatch<N, zip_with_index_<F, C>> {
    template <typename... Ts>
    using f = indexer<make_index_for_<sizeof...(Ts)>>::template f<
            F, dispatch<find_dispatch(sizeof...(Ts)), C>::template f, Ts...>;
};
template <std::size_t N, typename F, template <typename...> class C>
struct dispatch<N, zip_with_index_<F, lift_<C>>> {
    template <typename... Ts>
    using f = indexer<make_index_for_<sizeof...(Ts)>>::template f<F, C, Ts...>;
};

} // namespace impl

} // namespace boost::tmp

// TESTING:
namespace zip_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<3>, int_<7>>>)
struct AddPairsTogetherWithZip;

template<typename T, typename U>
using add = int_<T::value + U::value>;

template<typename T> requires(std::same_as<T, list_<list_<int_<1>, int_<2>>, list_<int_<3>, int_<4>>>>)
struct ZipPairsIntoList;

// Performs an addition of pairs of elements component wise i.e. (x0 + x1), (y0 + y1), ...
using zip_test_1 = AddPairsTogetherWithZip<call_<zip_<lift_<add>>, list_<int_<1>, int_<3>>, list_<int_<2>, int_<4>>>>;

// Pairs elements in each list together i.e. (x0, y0), (x1, y1), ...
using zip_test_2 = ZipPairsIntoList<call_<zip_<listify_>, list_<int_<1>, int_<3>>, list_<int_<2>, int_<4>>>>;

} // namespace zip_test

// TESTING:
namespace zip_with_index_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<list_<sizet_<0>, char_<'a'>>,
                                                    list_<sizet_<1>, char_<'b'>>,
                                                    list_<sizet_<2>, char_<'c'>>>>)
struct ZipABCWith123;
using test_one = ZipABCWith123<call_<zip_with_index_<>, char_<'a'>, char_<'b'>, char_<'c'>>>;
} // namespace zip_with_index_test
