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

export module Boost.TMP:Algorithm.Slide;

import :Algorithm.MakeSequence;
import :Algorithm.Tee;
import :Algorithm.Window;
import :Base.Types;

// TODO: Add incrementing by a number other than 1.

namespace boost::tmp {

// slide_ : Given a window size W, form a list of lists where each individual
// list is W elements long, starting at index 0 and incrementing until the last
// list contains the last element.
// at zero.
// Input params: Parameter pack
// Closure params: W - Positive integer type denoting the window size.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, T2, T3, T4, T5, ..., TN
// apply  -  (get W elements starting at index 0, incrementing through until the last element)
// result -  L(T0, ..., TW), L(T1, ... T(W + 1)), ..., L(T(W - N), TN)
// Empty return type: list_<>
template<typename W = sizet_<0>, typename C = listify_>
struct slide_ {};

// slide_ : implementation
namespace impl {

template<typename W, typename C = listify_, typename L = listify_>
struct slide_impl {};
template<std::size_t N, typename W, typename C, typename... Ts>
struct dispatch<N, slide_impl<W, list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<sizeof...(Us), tee_<window_<Ts, W>..., C>>::template f<Us...>;
};
template<std::size_t N, typename W, typename C>
struct dispatch<N, slide_<W, C>> {
    template<typename... Ts>
    using f = dispatch<N, slide_impl<W, make_index_for_<sizeof...(Ts) - W::value + 1>, C>>::template f<Ts...>;
};
template<typename W, typename C>
struct dispatch<0, slide_<W, C>> {
    template<typename... Ts>
    using f = dispatch<0, slide_impl<W, list_<sizet_<0>>, C>>::template f<>;
};

} // namespace impl

} // namespace boost::tmp

namespace sliding_test {

using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<list_<int_<1>, int_<2>>,
                                                    list_<int_<2>, int_<3>>,
                                                    list_<int_<3>, int_<4>>>>)
struct SlideTwoIncrByOne;
template<typename T> requires(std::same_as<T, list_<list_<int_<1>, int_<2>, int_<3>>, 
                                                    list_<int_<2>, int_<3>, int_<4>>>>)
struct SlideThreeIncrByOne;
            
template<typename T> requires(std::same_as<T, list_<list_<int_<1>, int_<2>, int_<3>, int_<4>>>>)
struct SlideFourIncrByOne;

using slide_test_1 = SlideTwoIncrByOne<call_<slide_<sizet_<2>>, int_<1>, int_<2>, int_<3>, int_<4>>>;
using slide_test_2 = SlideThreeIncrByOne<call_<slide_<sizet_<3>>, int_<1>, int_<2>, int_<3>, int_<4>>>;
using slide_test_3 = SlideFourIncrByOne<call_<slide_<sizet_<4>>, int_<1>, int_<2>, int_<3>, int_<4>>>;

} // namespace sliding_test

