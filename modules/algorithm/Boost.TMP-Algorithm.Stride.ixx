//  Copyright 2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Stride;

import :Algorithm.Index;
import :Algorithm.MakeSequence;
import :Algorithm.Tee;
import :Base.Types;

namespace boost::tmp {

// stride_ : Get every nth element in a parameter pack, starting
// at zero.
// Input params: Parameter pack
// Closure params: S - Positive integer type denoting the step of the stride.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, T2, T3, T4, T5, ..., TN
// apply  -  (get every nth element)
// result -  T0, T(n), T(2n), T(3n), ..., T(m * n)
// Empty return type: list_<>
template<typename S = sizet_<0>, typename C = listify_>
struct stride_ {};

// TODO: Move this to MakeSequence module.
template <std::size_t N>
using make_index_for_stride = make_seq_impl<next_state(0, N)>::template f<N>;

// stride_ : implementation
template<typename S, typename C = listify_, typename L = listify_>
struct tee_drops_ {};
template<std::size_t N, typename S, typename C, typename... Ts>
struct dispatch<N, tee_drops_<S, list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<sizeof...(Us) / S::value + 1, tee_<index_<sizet_<Ts::value * S::value>>..., C>>::template f<Us...>;
};
template<typename S, typename C, typename... Ts>
struct dispatch<0, tee_drops_<S, list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<0, tee_<i0_<>, C>>::template f<Us...>;
};

consteval std::size_t stride_div(std::size_t input_size, std::size_t stride_length) {
    return (input_size % stride_length) < 1
        ? input_size / stride_length
        : input_size / stride_length + 1;
}

template<std::size_t N, typename S, typename C>
struct dispatch<N, stride_<S, C>> {
    template<typename... Ts>
    using f = dispatch<N, tee_drops_<S, make_index_for_stride<stride_div(sizeof...(Ts), S::value)>, C>>::template f<Ts...>;
};
template<typename S, typename C>
struct dispatch<0, stride_<S, C>> {
    template<typename... Ts>
    using f = dispatch<0, tee_drops_<S, list_<sizet_<0>>, C>>::template f<>;
};

} // namespace boost::tmp

namespace stride_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>)
struct EveryZerothElement;

template<typename T> requires(std::same_as<T, list_<int_<0>, int_<2>, int_<4>>>)
struct EverySecondElement;

template<typename T> requires(std::same_as<T, list_<char_<'a'>, char_<'d'>, char_<'g'>>>)
struct EveryThirdElement;

using stride_test_2 = EveryThirdElement<call_<stride_<sizet_<3>>, char_<'a'>, char_<'b'>, char_<'c'>, char_<'d'>, char_<'e'>, char_<'f'>, char_<'g'>>>;

} // namespace stride_test
