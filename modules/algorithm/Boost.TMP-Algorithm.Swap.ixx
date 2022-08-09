//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#endif

export module Boost.TMP:Algorithm.Swap;

import :Base.Types;

namespace boost::tmp {
// swap_ : Swaps two variadic parametic pack values. Must be only two values.
export template <typename C = listify_>
struct swap_ {};

// swap_ : implementation
template <typename C>
struct dispatch<2, swap_<C>> {
    template <typename T, typename U>
    using f = dispatch<2, C>::template f<U, T>;
};
} // namespace boost::tmp

// TESTING:
namespace swap_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<0>>>)
struct ListOneZero;

using test_one = ListOneZero<call_<swap_<>, int_<0>, int_<1>>>;
} // namespace swap_test
