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

export module Boost.TMP:Sequence.Tee;

import :Base.Identity;
import :Base.Logic;
import :Base.Dispatch;
import :Sequence.PushFront;
import :Sequence.Rotate;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename... Fs>
    struct tee_ {};
    
    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                  typename dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
                  typename dispatch<find_dispatch(sizeof...(Ts)), L>::template f<Ts...>>;
    };
    // specialization for case where last closure is a forward
    template <typename N, typename C, typename... Fs>
    struct tee_impl<N, identity_, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Fs) + sizeof...(Ts)), C>::template
                    f<dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
                            Ts...>;
    };
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<1>, L, C, Fs...> {
        template <typename T0>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                  typename dispatch<1, Fs>::template f<T0>...,
                  typename dispatch<1, L>::template f<T0>>;
    };
    // specialization for case where last closure is a forward
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<1>, identity_, C, Fs...> {
        template <typename T0>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                  typename dispatch<1, Fs>::template f<T0>..., T0>;
    };
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<2>, L, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template
                     f<typename dispatch<2, Fs>::template f<T0, T1>...,
                       typename dispatch<2, L>::template f<T0, T1>>;
    };
    // specialization for case where last closure is a forward
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<2>, identity_, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 2), C>::template f<
                  typename dispatch<2, Fs>::template f<T0, T1>..., T0, T1>;
    };

    // in case the continuation is an and_

    template <bool b, typename C, typename... Fs>
    struct tee_and_impl;
    template <typename C, typename... Fs>
    struct tee_and_impl<false, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename... Fs>
    struct tee_and_impl<true, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_and_impl<true, C, F, Fs...> {
        template <typename... Ts>
        using f = tee_and_impl<dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
                Fs...>::template f<Ts...>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_and_impl_1;
    template <typename C, typename... Fs>
    struct tee_and_impl_1<false, C, Fs...> {
        template <typename T0>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename... Fs>
    struct tee_and_impl_1<true, C, Fs...> {
        template <typename T0>
        using f1 = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_and_impl_1<true, C, F, Fs...> {
        template <typename T0>
        using f = tee_and_impl<dispatch<1, F>::template f<T0>::value, C,
                                        Fs...>::template f<T0>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_and_impl_2;
    template <typename C, typename... Fs>
    struct tee_and_impl_2<false, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename... Fs>
    struct tee_and_impl_2<true, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_and_impl_2<true, C, F, Fs...> {
        template <typename T0, typename T1>
        using f = tee_and_impl<dispatch<2, F>::template f<T0, T1>::value, C,
                                        Fs...>::template f<T0, T1>;
    };

    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl<N, L, and_<identity_, C>, Fs...> : tee_and_impl<true, C, Fs..., L> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<1>, L, and_<identity_, C>, Fs...>
            : tee_and_impl_1<true, C, Fs..., L> {};
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<1>, identity_, and_<identity_, C>, Fs...>
            : tee_and_impl_1<true, C, Fs..., identity_> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<2>, L, and_<identity_, C>, Fs...>
            : tee_and_impl_2<true, C, Fs..., L> {};
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<2>, identity_, and_<identity_, C>, Fs...>
            : tee_and_impl_2<true, C, Fs..., identity_> {};

    // in case the continuation is an or_

    template <bool b, typename C, typename... Fs>
    struct tee_or_impl;
    template <typename C, typename... Fs>
    struct tee_or_impl<true, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename... Fs>
    struct tee_or_impl<false, C, Fs...> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_or_impl<false, C, F, Fs...> {
        template <typename... Ts>
        using f = tee_or_impl<
                dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
                Fs...>::template f<Ts...>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_or_impl_1;
    template <typename C, typename... Fs>
    struct tee_or_impl_1<true, C, Fs...> {
        template <typename T0>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename... Fs>
    struct tee_or_impl_1<false, C, Fs...> {
        template <typename T0>
        using f1 = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_or_impl_1<false, C, F, Fs...> {
        template <typename T0>
        using f = tee_or_impl<dispatch<1, F>::template f<T0>::value, C,
                                        Fs...>::template f<T0>;
    };
    template <bool b, typename C, typename... Fs>
    struct tee_or_impl_2;
    template <typename C, typename... Fs>
    struct tee_or_impl_2<true, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<true_>;
    };
    template <typename C, typename... Fs>
    struct tee_or_impl_2<false, C, Fs...> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <typename C, typename F, typename... Fs>
    struct tee_or_impl_2<false, C, F, Fs...> {
        template <typename T0, typename T1>
        using f = tee_or_impl<dispatch<2, F>::template f<T0, T1>::value, C,
                                        Fs...>::template f<T0, T1>;
    };

    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl<N, L, or_<identity_, C>, Fs...> : tee_or_impl<false, C, Fs..., L> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<1>, L, or_<identity_, C>, Fs...>
            : tee_or_impl_1<false, C, Fs..., L> {};
    template <typename C, typename... Fs>
    struct tee_impl<sizet_<1>, identity_, or_<identity_, C>, Fs...>
            : tee_or_impl_1<false, C, Fs..., identity_> {};
    template <typename L, typename C, typename... Fs>
    struct tee_impl<sizet_<2>, L, or_<identity_, C>, Fs...>
            : tee_or_impl_2<false, C, Fs..., L> {};

    template <std::size_t N, typename F0, typename F1, typename... Fs>
    struct dispatch<N, tee_<F0, F1, Fs...>>
        : dispatch<find_dispatch(sizeof...(Fs) + 2),
                    rotate_<sizet_<sizeof...(Fs)>, push_front_<sizet_<N>, lift_<tee_impl>>>>::
                    template f<F0, F1, Fs...> {};
} // namespace boost::tmp

// TESTING:
namespace boost::tmp::test {

} // namespace boost::tmp::test
