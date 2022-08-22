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

export module Boost.TMP:Algorithm.Take;

import :Algorithm.Drop;
import :Algorithm.Rotate;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// take_ :
export template <typename N = sizet_<0>, typename C = listify_>
struct take_ {};

// take_ : implementation
namespace impl {

template <std::size_t N, typename P, typename C>
struct dispatch<N, take_<P, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)),
                    rotate_<P, drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>>::template f<Ts...>;
};

} // namespace impl

// take_last_ :
export template<typename N = sizet_<0>, typename C = listify_>
struct take_last_ {};

// take_last_ : implementation
namespace impl {

template<std::size_t N, typename P, typename C>
struct dispatch<N, take_last_<P, C>> {
    template<typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>::template f<Ts...>;
};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, list_<int_<1>>>)
struct TakeFirstElement_One;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>>>)
struct TakeFirstTwoElements_OneTwo;

using take_test_1 = TakeFirstElement_One<call_<take_<uint_<1>>, int_<1>, int_<2>, int_<3>>>;
using take_test_2 = TakeFirstTwoElements_OneTwo<call_<take_<uint_<2>>, int_<1>, int_<2>, int_<3>>>;

// UNDER CONSIDERATION: Taking more than the list results in compilation failure.
// UNDER CONSIDERATION: Taking from an empty input results in compilation failure.
// list_<>{} = call_<take_<uint_<4>>>{};

template<typename T> requires(std::same_as<T, list_<int_<4>, int_<5>>>)
struct LastTwoElements;

using take_last_test_1 = LastTwoElements<call_<take_last_<int_<2>>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>;

} // namespace test

} // namespace boost::tmp
