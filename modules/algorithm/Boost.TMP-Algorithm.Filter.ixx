//  Copyright 2018 Odin Holmes.
//			  2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Filter;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

// filter_ :
export template <typename F, typename C = listify_>
struct filter_ {};

// filter_ : implementation
namespace impl {

template <std::size_t N, template <typename...> class F, typename C>
struct filtery;
template <template <typename...> class F, typename C>
struct filtery<0, F, C> {
    template <std::size_t N, typename T, typename U, typename... Ts>
    using f = filtery<(F<U>::value + 2 * (N == 1)), F,
                                C>::template f<(N - 1), U, Ts...>;
};
template <template <typename...> class F, typename C>
struct filtery<1, F, C> {
    template <std::size_t N, typename T, typename U, typename... Ts>
    using f = filtery<(F<U>::value + 2 * (N == 1)), F, C>::template
                    f<(N - 1), U, Ts..., T>;
};
template <template <typename...> class F, typename C>
struct filtery<2, F, C> { // all the way around, remove last
    template <std::size_t N, typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
};
template <template <typename...> class F, typename C>
struct filtery<3, F, C> { // all the way around, keep last
    template <std::size_t N, typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, filter_<lift_<F>, C>> {
    template <typename T, typename... Ts>
    using f = filtery<(F<T>::value + 2 * (sizeof...(Ts) == 0)), F,
                                C>::template f<(sizeof...(Ts)), T, Ts...>;
};
template <std::size_t N, typename F, typename C>
struct dispatch<N, filter_<F, C>> {
    template <typename T, typename... Ts>
    using f = filtery<
            (dispatch<1, F>::template f<T>::value + 2 * (sizeof...(Ts) == 0)),
            dispatch<1, F>::template f, C>::template f<(sizeof...(Ts)), T, Ts...>;
};
template <typename F, typename C>
struct dispatch<0, filter_<F, C>> {
    template <typename... Ts>
    using f = dispatch<0, C>::template f<>;
};
template <template <typename...> class F, typename C>
struct dispatch<0, filter_<lift_<F>, C>> {
    template <typename... Ts>
    using f = dispatch<0, C>::template f<>;
};

} // namespace impl

} // namespace boost::tmp

// TESTING:
namespace filter_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<2>, int_<4>, int_<6>, int_<8>, int_<10>>>)
struct FilterOutOddNumbers;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using test_one = FilterOutOddNumbers<call_<filter_<lift_<is_even>>,
            int_<1>, int_<2>, int_<3>, int_<4>, int_<5>,
            int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>>;
} // namespace filter_test
