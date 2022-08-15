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

import :Algorithm.FunctionIf;
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

// stride_ : implementation
template<typename StrideLength>
struct stride_helper {
    template<typename I>
    using f = bool_<(I::value % StrideLength::value != 0)>;
};
// FIXME: Add specialization for stride_<sizet_<0>>
template<std::size_t N, typename S, typename C>
struct dispatch<N, stride_<S, C>> : dispatch<N, remove_if_<lift_<stride_helper<S>::template f>, C>> {};

} // namespace boost::tmp

namespace stride_test {
using namespace boost::tmp;

// template<typename T> requires(std::same_as<T, list_<int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>)
// struct EveryZerothElement;

template<typename T> requires(std::same_as<T, list_<int_<0>, int_<2>, int_<4>>>)
struct EverySecondElement;

template<typename T> requires(std::same_as<T, list_<int_<0>, int_<3>, int_<6>>>)
struct EveryThirdElement;

using stride_test_1 = EverySecondElement<call_<stride_<sizet_<2>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>;

using stride_test_2 = EveryThirdElement<call_<stride_<sizet_<3>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>, int_<6>>>;

} // namespace stride_test

