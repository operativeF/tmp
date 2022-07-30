//  Copyright 2021-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Algorithm.Pairing;

import :Base.Lift;
import :Base.Vocabulary;
import :Base.Dispatch;
import :Sequence.Join;

namespace boost::tmp {
    export template <typename F = listify_, typename C = listify_>
    struct pairing_ {};

    template <template <typename...> class F, typename T, typename... Ts>
    using pairing_helper = list_<F<T, Ts>...>;

    template <template <typename...> class F, typename C, typename T, typename U>
    struct pairing_unpacker {};

    template <template <typename...> class F, typename C, typename... Ts, typename... Us>
    struct pairing_unpacker<F, C, list_<Ts...>, list_<Us...>> {
        using type = dispatch<find_dispatch(sizeof...(Ts)),
                                    join_<C>>::template f<pairing_helper<F, Ts, Us>...>;
    };

    template <template <typename...> class F, typename C>
    struct dispatch<2, pairing_<lift_<F>, C>> {
        template <typename T, typename U>
        using f = pairing_unpacker<F, C, T, U>::type;
    };

    template <typename F, typename C>
    struct dispatch<2, pairing_<F, C>>
            : dispatch<2, pairing_<lift_<dispatch<2, F>::template f>, C>> {};
} // namespace boost::tmp
