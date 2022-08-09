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

export module Boost.TMP:Sequence.RepeatSequence;

import :Base.Types;
import :Sequence.Join;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template<typename N = sizet_<0>, typename C = listify_>
    struct repeat_sequence_{};

    consteval std::size_t repeat_select(std::size_t N) {
        return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
    }

    template <std::size_t, typename C>
    struct repeat_seq_impl;

    template <typename C>
    struct repeat_seq_impl<0, C> {
        template <typename...>
        using f = dispatch<0, C>::template f<>;
    };

    template <typename C>
    struct repeat_seq_impl<1, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 1, C>::template f<T, Ts...>;
    };

    template <typename C>
    struct repeat_seq_impl<2, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 2, C>::template f<T, T, Ts...>;
    };

    template <typename C>
    struct repeat_seq_impl<3, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 3, C>::template f<T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<4, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 4, C>::template f<T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<5, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 5, C>::template f<T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<6, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 6, C>::template f<T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<7, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 7, C>::template f<T, T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<8, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 8, C>::template f<T, T, T, T, T, T, T, T, Ts...>;
    };
    template <typename C>
    struct repeat_seq_impl<16, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 16, C>::template f<T, T, T, T, T, T, T, T,
                                                              T, T, T, T, T, T, T, T, Ts...>;
    };

    template <typename C>
    struct repeat_seq_impl<32, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 32, C>::template f<T, T, T, T, T, T, T, T,
                                                              T, T, T, T, T, T, T, T,
                                                              T, T, T, T, T, T, T, T,
                                                              T, T, T, T, T, T, T, T, Ts...>;
    };

    template <typename C>
    struct repeat_seq_impl<64, C> {
        template <typename T, typename... Ts>
        using f = dispatch<sizeof...(Ts) + 64, C>::template f<
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T,
                T, T, T, T, T, T, T, T, Ts...>;
    };

    template <std::size_t P, typename C, std::size_t Step = repeat_select(P)>
    struct make_repeat : repeat_seq_impl<Step, repeat_sequence_<sizet_<(P - Step) + 1>, C>> {};

    template <std::size_t P, typename C>
    struct make_repeat<P, C, P> : repeat_seq_impl<P, C> {};

    template <std::size_t N, typename P, typename C>
    struct dispatch<N, repeat_sequence_<P, C>> : make_repeat<P::value, C> {};
} // namespace boost::tmp

// TESTING:
namespace repeat_sequence_test {
    using namespace boost::tmp;

    // TODO: Implement repeat_sequence_test
    // std::index_sequence<1, 1, 1, 1, 1, 1, 1, 1, 1, 1>{} = call_<repeat_sequence_<sizet_<10>, lift_<into_sequence>>, sizet_<1>>{};
    // list_<sizet_<1>, sizet_<1>, sizet_<1>, sizet_<2>, sizet_<2>, sizet_<2>, sizet_<3>, sizet_<3>, sizet_<3>>{} = call_<transform_<repeat_sequence_<sizet_<3>>, join_<>>, sizet_<1>, sizet_<2>, sizet_<3>>{};
} // namespace repeate_sequence_test
