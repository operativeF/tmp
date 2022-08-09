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

export module Boost.TMP:Sequence.Size;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename C = identity_>
    struct size_ {};

    template <std::size_t N, typename C>
    struct dispatch<N, size_<C>> {
        template <typename... Ls>
        using f = dispatch<1, C>::template f<sizet_<sizeof...(Ls)>>;
    };
} // namespace boost::tmp

// TESTING:
namespace size_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, sizet_<3>>)
    struct ThreeElementsInPack;

    template<typename T> requires(std::same_as<T, sizet_<0>>)
    struct EmptyPackIsZero;

    using test_one = ThreeElementsInPack<call_<size_<>, int_<0>, int_<2>, int_<4>>>;

    // No input list is zero size.
    using test_two = EmptyPackIsZero<call_<size_<>>>;

} // namespace size_test
