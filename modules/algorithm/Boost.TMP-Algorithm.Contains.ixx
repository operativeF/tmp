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

export module Boost.TMP:Algorithm.Contains;

import :Algorithm.Logic;
import :Algorithm.Slide;
import :Base.Types;

#ifdef _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

// contains_ : Given a type (V), return true_ / false_ on whether a given VPP
// contains the type V.
export template <typename T, typename C = identity_>
struct contains_ {};

// contains_ : implementation
namespace impl {

template <std::size_t N, typename T, typename C>
struct dispatch<N, contains_<T, C>> : dispatch<N, or_<is_<T>, C>> {};

} // namespace impl

// contains_subrange_ :
export template<typename L, typename C = identity_>
struct contains_subrange_ {};

namespace impl {

template<std::size_t N, typename C, typename... Ts>
struct dispatch<N, contains_subrange_<list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<sizeof...(Us), slide_<sizet_<sizeof...(Ts)>, contains_<list_<Ts...>, C>>>::template f<Us...>;
};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, false_>)
struct DoesNotContainType;

template<typename T> requires(std::same_as<T, true_>)
struct ContainsType;

using contains_test_1   = DoesNotContainType<call_<contains_<int_<0>>, int_<1>>>;

using contains_test_2   = ContainsType<call_<contains_<int_<2>>, int_<0>, int_<1>, int_<2>>>;

using contains_test_3   = DoesNotContainType<call_<contains_<int_<1>>>>;

template<typename T> requires(std::same_as<T, true_>)
struct ContainsSubrange123;

using contains_subrange_test_1 = ContainsSubrange123<call_<contains_subrange_<list_<int_<1>, int_<2>, int_<3>>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<4>>>;

} // namespace test

} // namespace boost::tmp


