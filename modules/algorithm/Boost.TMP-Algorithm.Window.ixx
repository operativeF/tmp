//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Window;

import :Algorithm.Core;
import :Algorithm.Take;
import :Base.Types;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

// window_ :
export template<typename StartIndex, typename Count, typename C = listify_>
struct window_ {};

// window_ : implemenation
namespace impl {

template<std::size_t N, typename StartIndex, typename Count, typename C>
struct dispatch<N, window_<StartIndex, Count, C>> {
    template<typename... Ts>
    using f = dispatch<sizeof...(Ts), drop_<StartIndex, take_<Count, C>>>::template f<Ts...>;
};

} // namespace impl

#ifdef TMP_COMPILE_TIME_TESTING
namespace test {

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
struct GetTheMiddle123;

using window_test_1 = GetTheMiddle123<call_<window_<int_<1>, int_<3>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<5>, int_<7>>>;

} // namespace test
#endif // TMP_COMPILE_TIME_TESTING

} // namespace boost::tmp
