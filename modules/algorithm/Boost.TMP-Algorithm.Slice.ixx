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

export module Boost.TMP:Algorithm.Slice;

import :Algorithm.Core;
import :Base.Types;

namespace boost::tmp {

template<typename LowerB, typename UpperB, typename C = listify_>
struct slice_ {};

namespace impl {

template<std::size_t N, typename LowerB, typename UpperB, typename C>
struct dispatch<N, slice_<LowerB, UpperB, C>> : dispatch<N, drop_<LowerB, drop_last_<UpperB, C>>> {};

} // namespace impl

#ifdef TMP_COMPILE_TIME_TESTING
namespace test {

template<typename T> requires(std::same_as<T, list_<int_<5>, int_<6>, int_<7>, int_<8>>>)
struct SliceLBFourUBTwo;

using slice_test_1 = SliceLBFourUBTwo<call_<slice_<sizet_<4>, sizet_<2>>,
                                            int_<1>, int_<2>, int_<3>, int_<4>, int_<5>,
                                            int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>>;

} // namespace test
#endif // TMP_COMPILE_TIME_TESTING

} // namespace boost::tmp
