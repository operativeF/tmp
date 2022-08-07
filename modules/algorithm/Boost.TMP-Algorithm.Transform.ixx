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

export module Boost.TMP:Algorithm.Transform;

import :Base.Identity;
import :Base.Lift;
import :Base.List;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename F = identity_, typename C = listify_>
    struct transform_ {};
    
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, transform_<F, C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<
                     typename dispatch<1, F>::template f<Ts>...>;
    };

    template <std::size_t N, template <typename...> class F, typename FC, typename C>
    struct dispatch<N, transform_<lift_<F, FC>, C>> {
        template <typename... Ts>
        using f = dispatch<(N + (N > sizeof...(Ts))), C>::template f<F<Ts>...>;
    };
} // namespace boost::tmp

// TESTING:
namespace boost::tmp::test {

} // namespace boost::tmp::test
