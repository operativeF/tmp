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

export module Boost.TMP:Algorithm.Split;

import :Algorithm.Drop;
import :Algorithm.Take;
import :Algorithm.Tee;
import :Base.Types;

namespace boost::tmp {

template<typename I = sizet_<0>, typename C = listify_>
struct split_ {};

namespace impl {

template<std::size_t N, typename I, typename C>
struct dispatch<N, split_<I, C>> : dispatch<N, tee_<take_<I>, drop_<I>, listify_>> {};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, list_<list_<int_<1>, int_<2>, int_<3>, int_<4>>,
                                                    list_<int_<5>, int_<6>, int_<7>, int_<8>>>>)
struct SplitAtIndexFour;

using split_test_1 = SplitAtIndexFour<call_<split_<sizet_<4>>, int_<1>, int_<2>, int_<3>, int_<4>,
                                                               int_<5>, int_<6>, int_<7>, int_<8>>>;

} // namespace test

} // namespace boost::tmp
