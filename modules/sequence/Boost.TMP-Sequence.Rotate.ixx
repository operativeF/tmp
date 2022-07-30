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

export module Boost.TMP:Sequence.Rotate;

import :Base.Integral;
import :Base.List;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename N = sizet_<0>, typename C = listify_>
    struct rotate_ {};

    consteval std::size_t rotate_select(std::size_t N) {
        return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
    }
    template <std::size_t, typename C>
    struct rotate_impl;
    template <typename C>
    struct rotate_impl<0, C> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
    };
    template <typename C>
    struct rotate_impl<1, C> {
        template <typename T, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
    };
    template <typename C>
    struct rotate_impl<2, C> {
        template <typename T0, typename T1, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 2),
                             C>::template f<Ts..., T0, T1>;
    };
    template <typename C>
    struct rotate_impl<3, C> {
        template <typename T0, typename T1, typename T2, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 3),
                           C>::template f<Ts..., T0, T1, T2>;
    };
    template <typename C>
    struct rotate_impl<4, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 4),
                           C>::template f<Ts..., T0, T1, T2, T3>;
    };
    template <typename C>
    struct rotate_impl<5, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                    typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 5),
                           C>::template f<Ts..., T0, T1, T2, T3, T4>;
    };
    template <typename C>
    struct rotate_impl<6, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                    typename T5, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 6),
                           C>::template f<Ts..., T0, T1, T2, T3, T4, T5>;
    };
    template <typename C>
    struct rotate_impl<7, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                    typename T5, typename T6, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 7),
                           C>::template f<Ts..., T0, T1, T2, T3, T4, T5, T6>;
    };
    template <typename C>
    struct rotate_impl<8, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                    typename T5, typename T6, typename T7, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 8),
                           C>::template f<Ts..., T0, T1, T2, T3, T4, T5, T6, T7>;
    };
    template <typename C>
    struct rotate_impl<16, C> {
        template <typename T0, typename T1, typename T2, typename T3, typename T4,
                    typename T5, typename T6, typename T7, typename T8, typename T9,
                    typename T10, typename T11, typename T12, typename T13, typename T14,
                    typename T15, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 16),
                           C>::template f<Ts..., T0, T1, T2,  T3,  T4,  T5,  T6,  T7,
                                                 T8, T9, T10, T11, T12, T13, T14, T15>;
    };
    template <typename C>
    struct rotate_impl<32, C> {
        template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                 typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                 typename T10, typename T11, typename T12, typename T13, typename T14,
                 typename T15, typename T16, typename T17, typename T18, typename T19,
                 typename T20, typename T21, typename T22, typename T23, typename T24,
                 typename T25, typename T26, typename T27, typename T28, typename T29,
                 typename T30, typename T31, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 32), C>::template
                     f<Ts..., T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,
                              T8,  T9,  T10, T11, T12, T13, T14, T15,
                              T16, T17, T18, T19, T20, T21, T22, T23,
                              T24, T25, T26, T27, T28, T29, T30, T31>;
    };
    template <typename C>
    struct rotate_impl<64, C> {
        template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
                  typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
                  typename T10, typename T11, typename T12, typename T13, typename T14,
                  typename T15, typename T16, typename T17, typename T18, typename T19,
                  typename T20, typename T21, typename T22, typename T23, typename T24,
                  typename T25, typename T26, typename T27, typename T28, typename T29,
                  typename T30, typename T31, typename T32, typename T33, typename T34,
                  typename T35, typename T36, typename T37, typename T38, typename T39,
                  typename T40, typename T41, typename T42, typename T43, typename T44,
                  typename T45, typename T46, typename T47, typename T48, typename T49,
                  typename T50, typename T51, typename T52, typename T53, typename T54,
                  typename T55, typename T56, typename T57, typename T58, typename T59,
                  typename T60, typename T61, typename T62, typename T63, typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts) + 64), C>::template
                     f<Ts..., T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10,
                              T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                              T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32,
                              T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
                              T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
                              T55, T56, T57, T58, T59, T60, T61, T62, T63>;
    };
    template <typename P, typename C>
    struct dispatch<0, rotate_<P, C>> {
        template <typename...>
        using f = dispatch<0, C>::template f<>;
    };
    template <std::size_t P, typename C, std::size_t Step = rotate_select(P)>
    struct make_rotate
        : rotate_impl<rotate_select(Step), rotate_<sizet_<(P - Step)>, C>> { /* not done */
    };
    template <std::size_t P, typename C>
    struct make_rotate<P, C, P> : rotate_impl<P, C> {};

    template <std::size_t N, typename P, typename C>
    struct dispatch<N, rotate_<P, C>> : make_rotate<P::value, C> {};
} // namespace boost::tmp
