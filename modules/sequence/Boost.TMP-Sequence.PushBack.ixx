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

export module Boost.TMP:Sequence.PushBack;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// push_back_ :
export template <typename T, typename C = listify_>
struct push_back_ {};

// push_back_ : implementation
template <std::size_t N, typename T, typename C>
struct dispatch<N, push_back_<T, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
};
} // namespace boost::tmp

// TESTING:
namespace push_back_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, char_<'c'>>>)
    struct PushBack_C {};

    using test_one = PushBack_C<call_<push_back_<char_<'c'>>, int_<1>, int_<2>>>;

} // namespace push_back_test
