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

export module Boost.TMP:Algorithm.Unique;

import :Algorithm.Drop;
import :Algorithm.Flatten;
import :Algorithm.Fold;
import :Algorithm.Index;
import :Algorithm.Logic;
import :Algorithm.PushPop;
import :Base.Types;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

template<typename F = identity_, typename C = listify_>
struct unique_ {};

namespace impl {

template <typename T>
struct unique_magic_type;

// Our starting point; gets dropped off at the end.
struct unique_super_base {
    static consteval bool contains(void *) {
        return false;
    }
};
template <typename Tail, typename T>
struct unique_base : Tail {
    static consteval bool contains(unique_magic_type<T> *) {
        return true;
    }

    using Tail::contains;
};

template <typename T, typename U>
using is_in_set = bool_<T::contains(static_cast<unique_magic_type<U> *>(0))>;

using unique_push_if = if_<lift_<is_in_set>, front_<>, lift_<unique_base>>;

template<std::size_t N, typename F, typename C>
struct dispatch<N, unique_<F, C>> {
    template<typename... Ts>
    using f = dispatch<N, push_front_<unique_super_base, fold_left_<unique_push_if, flatten_<drop_<uint_<1>, C>>>>>::template f<Ts...>;
};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, list_<int_<3>, int_<1>, int_<2>>>)
struct OnlyUniqueNums;

using unique_test_1 = OnlyUniqueNums<call_<unique_<>, int_<3>, int_<1>, int_<2>, int_<2>, int_<1>, int_<2>>>;

} // namespace test

} // namespace boost::tmp
