//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#include <type_traits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Call;

import :Base.Identity;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    template <typename F, typename... Ts> // workaround for old clang
    struct call_impl {
        using type = dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>;
    };

    export template <typename F, typename... Ts>
    using call_ = dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>;

    export template <typename T, typename... Ts>
    using call_t = dispatch<find_dispatch(sizeof...(Ts)), T>::template
                      f<Ts...>::type;

    export template <typename T, typename... Ts>
    constexpr auto call_v = dispatch<find_dispatch(sizeof...(Ts)), T>::template
                               f<Ts...>::value;

    export template <typename C = identity_>
    struct call_f_ {};

    template <std::size_t N, typename C>
    struct dispatch<N, call_f_<C>> {
        template <typename F, typename... Ts>
        using f = dispatch<1, C>::template f<
                     typename dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>>;
    };
} // namespace boost::tmp
