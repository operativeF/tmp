//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.If;

import :Base.Always;
import :Base.Lift;
import :Base.List;
import :Base.Nothing;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    /// \brief Given a predicate P, if true, return T, and if false, return F.
    export template <typename P, typename T, typename F = always_<nothing_>>
    struct if_ {};

    template <bool B>
    struct if_impl;

    template <>
    struct if_impl<true> {
        template <typename T, typename U>
        using f = T;
    };

    template <>
    struct if_impl<false> {
        template <typename T, typename U>
        using f = U;
    };

    template <typename P, typename T, typename F>
    struct dispatch<1, if_<P, T, F>> {
        template <typename T0>
        using f = dispatch<1, typename if_impl<dispatch<1, P>::template f<T0>::value>::template f<T, F>>::template f<T0>;
    };

    template <template <typename...> class P, typename T, typename F>
    struct dispatch<1, if_<lift_<P>, T, F>> {
        template <typename T0>
        using f = dispatch<1, typename if_impl<P<T0>::value>::template f<T, F>>::template f<T0>;
    };

    template <std::size_t N, typename P, typename T, typename F>
    struct dispatch<N, if_<P, T, F>> {
        template <typename... Ts>
        using f = dispatch<
                find_dispatch(sizeof...(Ts)),
                typename if_impl<dispatch<find_dispatch(sizeof...(Ts)), P>::template f<
                        Ts...>::value>::template f<T, F>>::template f<Ts...>;
    };
    template <std::size_t N, template <typename...> class P, typename T, typename F>
    struct dispatch<N, if_<lift_<P>, T, F>> {
        template <typename... Ts>
        using f = dispatch<
                find_dispatch(sizeof...(Ts)),
                typename if_impl<P<Ts...>::value>::template f<T, F>>::template f<Ts...>;
    };
    template <template <typename...> class P, typename T, typename F>
    struct dispatch<2, if_<lift_<P>, T, F>> {
        template <typename T0, typename T1>
        using f = dispatch<2,
                  typename if_impl<P<T0,T1>::value>::template f<T, F>>::template f<T0,T1>;
    };
    template <template <typename...> class P>
    struct dispatch<1, if_<lift_<P>, listify_, always_<list_<>>>> {
        template <typename U>
        using f = if_impl<P<U>::value>::template f<list_<U>, list_<>>;
    };
} // namespace boost::tmp
